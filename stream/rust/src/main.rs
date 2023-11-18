use reqwest::Client;
use rust::{stream_handler::StreamHandler, request_stream_handler::RequestStreamHandler, stream::Chunk};
use tokio::io::{self, AsyncBufReadExt, BufReader};
use futures::stream::{StreamExt, self}; // Corrected import

#[tokio::main]
async fn main() -> io::Result<()> {
    // Create a new client
    let client = Client::new();

    let stream_handler = RequestStreamHandler::new(client);

    let mut stream = stream_handler.get_stream().await;
    while let Some(chunk_result) = stream.next().await {
        match chunk_result {
            Ok(chunk) => {
                // If the chunk is Ok, process it
                process_chunk(&chunk).await; // Assuming process_chunk is an async function
            },
            Err(e) => {
                // If there's an error, handle it (e.g., logging or recovering)
                eprintln!("Error processing chunk: {:?}", e);
            },
        }
    }
    Ok(())
}

// Here's the async function to process each chunk
async fn process_chunk(chunk: &Chunk) {
    // Process the chunk as needed. For example:
    println!("Received a chunk with id: {:?}", chunk.choices[0].delta.content);
    // ... additional processing ...
}

async fn non_abstraction_way(client: Client) {
    // Make a GET request to the specific route
    let mut response = client
        .get("http://127.0.0.1:3000/stream")
        .send()
        .await
        .expect("Failed to send request");

    // Check if the request was successful
    if response.status().is_success() {
        // Use bytes_stream to get a stream of chunks
        let mut stream = response.bytes_stream();

        // Prepare stdin to read user input
        let stdin = io::stdin();
        let mut stdin = BufReader::new(stdin);

        // Stream the response body
        while let Some(chunk) = stream.next().await {
            match chunk {
                Ok(bytes) => {
                    // Process each chunk as it arrives
                    process_chunk_byte(&bytes).await;

                    // Wait for the user to press Enter
                    let mut user_input = String::new();
                    println!("Press Enter to continue...");
                    stdin.read_line(&mut user_input).await.expect("Failed to read line");
                },
                Err(e) => {
                    eprintln!("Error while reading the chunk: {}", e);
                    break;
                }
            }
        }
    } else {
        eprintln!("Received a non-success status code: {}", response.status());
    }
}

async fn process_chunk_byte(chunk: &[u8]) {
    // Here we're just printing the chunk, but you could process it as needed
    print!("{}", String::from_utf8_lossy(chunk));
}