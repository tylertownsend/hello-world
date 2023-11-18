use std::error::Error;

use async_trait::async_trait;
use futures::StreamExt;
use reqwest::Client;

use crate::stream::{CompletionStream, Chunk, Delta, Choice};
use crate::stream_handler::StreamHandler;

// The struct that will hold your API client or context
pub struct RequestStreamHandler {
    api_client: Client, // Assume `ApiClient` has the `create_stream` method.
}

impl RequestStreamHandler {
    pub fn new(api_client: Client) -> RequestStreamHandler {
        RequestStreamHandler {
            api_client
        }
    }
}

// The implementation of `StreamHandler` for `ChatStreamHandler`
#[async_trait]
impl StreamHandler for RequestStreamHandler {
    type Item = Chunk;
    type Error = Box<dyn Error>;
    type Stream = CompletionStream; // Alias from your API definition

        // Convert the response into a Stream of bytes, then map each chunk to your desired type
    async fn get_stream(&self) -> Self::Stream {
    // Call the API to create and get the stream
    let response = self.api_client.get("http://127.0.0.1:3000/stream")
        .send()
        .await
        .expect("Failed to send request");

        // Convert the response into a Stream of bytes, then map each chunk to your desired type
        // The map method in a stream pipeline is applied lazily to each item as it is produced by the stream.
        // This means that the conversion from Bytes to ChatCompletionChunck and the subsequent error handling
        // will be applied individually to each item (each chunk of data) as it is emitted by the bytes_stream.
        let stream = response
            .bytes_stream()
            .map(|result| {
                result
                    .map_err(|e| Box::new(e) as Box<dyn Error>) // Convert reqwest::Error into Box<dyn Error>
                    .and_then(|bytes_chunk| {
                        // Convert the chunk into a UTF-8 String
                        let content = String::from_utf8(bytes_chunk.to_vec())
                            .map_err(|e| Box::new(e) as Box<dyn Error>)?;

                        // Here we're constructing the ChatCompletionDelta with the content
                        let delta = Delta {
                            content: Some(content),
                        };

                        // Construct the ChatChoice with the delta
                        let choice = Choice {
                            index: 0, // Placeholder value
                            delta,
                            finish_reason: None, // Placeholder value
                        };

                        // Finally, create the ChatCompletionChunck
                        Ok(Chunk{
                            id: None, // Placeholder value
                            choices: vec![choice],
                        })
                    })
            })
            .boxed();
        // Box the stream and pin it
        Box::pin(stream)
    }
}