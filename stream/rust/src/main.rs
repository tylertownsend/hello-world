use reqwest::Client;
use tokio::io::{self, AsyncBufReadExt, BufReader};
use futures::stream::StreamExt; // Corrected import

#[tokio::main]
async fn main() -> io::Result<()> {
    // Create a new client
    let client = Client::new();

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
                    process_chunk(&bytes).await;

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

    Ok(())
}

async fn process_chunk(chunk: &[u8]) {
    // Here we're just printing the chunk, but you could process it as needed
    print!("{}", String::from_utf8_lossy(chunk));
}