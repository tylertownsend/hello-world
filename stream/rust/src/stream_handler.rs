use async_trait::async_trait;
use futures::stream::Stream;
use std::pin::Pin;

// Define a trait with an associated type that implements the Stream trait.
#[async_trait]
pub trait StreamHandler {
    type Item;
    type Error;
    type Stream: Stream<Item = Result<Self::Item, Self::Error>> + Send + 'static;

    // Define a method that will return a stream.
    async fn get_stream(&self) -> Self::Stream;
}
