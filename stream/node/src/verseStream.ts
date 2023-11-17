import { Readable } from 'stream';

class VerseStream extends Readable {
  private lines: string[];
  private currentIndex: number;

  constructor(verseAndChorus: string, options?: ConstructorParameters<typeof Readable>[0]) {
    super(options);
    // Split the input text into lines
    this.lines = verseAndChorus.split('\n');
    this.currentIndex = 0;
  }

  _read(size: number): void {
    // Check if there are lines left to send
    if (this.currentIndex < this.lines.length) {
      // Push the current line to the stream and increment the index
      this.push(this.lines[this.currentIndex] + '\n');
      this.currentIndex++;
    } else {
      // Push null to signal the end of the stream
      this.push(null);
    }
  }
}

export default VerseStream;
