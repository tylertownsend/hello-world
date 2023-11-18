use futures::{Stream, task::{Context, Poll}};
use std::pin::Pin;
use reqwest::{Client, Error, Response};
use bytes::Bytes;
use std::future::Future;
use std::task::{Waker};

// Define our custom stream type.
struct MyStream {
    client: Client,
    url: String,
    response_future: Option<Pin<Box<dyn Future<Output = Result<Response, Error>> + Send>>>,
}

impl MyStream {
    // Create a new instance of `MyStream`.
    pub fn new(url: String) -> Self {
        Self {
            client: Client::new(),
            url,
            response_future: None, // No future to start with
        }
    }
}

impl Stream for MyStream {
    type Item = Result<Bytes, Error>;

    fn poll_next(mut self: Pin<&mut Self>, cx: &mut Context<'_>) -> Poll<Option<Self::Item>> {
        if self.response_future.is_none() {
            // We don't have a future, so we need to start the request
            let future = Box::pin(self.client.get(&self.url).send());
            self.response_future = Some(future);
        }

        let future = self.response_future.as_mut().unwrap();

        // Poll the future
        match future.as_mut().poll(cx) {
            Poll::Ready(Ok(response)) => {
                // We've got the response, remove the future as it's completed
                self.response_future.take();

                // Here you'd normally start another future to read the response body in chunks
                // For now, let's just say the stream is done.
                Poll::Ready(None)
            },
            Poll::Ready(Err(e)) => {
                // An error occurred, remove the future and return the error
                self.response_future.take();
                Poll::Ready(Some(Err(e)))
            },
            Poll::Pending => {
                // The future is not ready yet, so we need to be polled again later
                Poll::Pending
            }
        }
    }
}
