use std::pin::Pin;

use futures::Stream;
use serde::{Deserialize, Serialize};

#[derive(Debug, Deserialize, Serialize, Clone, PartialEq)]
pub struct Delta {
    pub content: Option<String>,
}

#[derive(Debug, Deserialize, Serialize, Clone, PartialEq)]
pub struct Choice {
    pub index: u32,
    pub delta: Delta,
    pub finish_reason: Option<String>,
}

#[derive(Debug, Deserialize, Clone, PartialEq, Serialize)]
pub struct Chunk {
    pub id: Option<String>,
    pub choices: Vec<Choice>,
}

pub type CompletionStream =
    Pin<Box<dyn Stream<Item = Result<Chunk, Box<dyn std::error::Error>>> + Send>>;