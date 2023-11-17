import { App } from "./app";
import VerseStream from "./verseStream";

const app = new App();

// Define routes for different endpoints
app.get('/', (req, res) => {
  res.end('Welcome to the homepage!');
});

app.get('/stream', (req, res) => {
  const firstVerse = `Yo VIP, let's kick it
    Ice, ice, baby
    Ice, ice, baby

    Alright stop, collaborate and listen
    Ice is back with the brand new invention
    Something grabs a hold of me tightly
    Flow like a harpoon daily and nightly
    "Will it ever stop?" Yo, I don't know
    Turn off the lights, huh, and I'll glow
    To the extreme, I rock a mic like a vandal
    Light up a stage and wax a chump like a candle
    Dance, rush the speaker that booms
    I'm killing your brain like a poisonous mushroom
    Deadly when I play a dope melody
    Anything less than the best is a felony
    Love it or leave it, you better gangway
    You better hit the bullseye, the kid don't play
    And if there was a problem, yo, I'll solve it
    Check out the hook while my DJ revolves it

    Ice, ice, baby
    Vanilla Ice, ice, baby
    Vanilla Ice, ice, baby
    Vanilla Ice, ice, baby`; // First verse text
  const verseStream = new VerseStream(firstVerse);
  res.setHeader('Content-Type', 'text/plain');
  verseStream.pipe(res); // Pipe the verse stream to the response object
});

app.listen(3000, () => {
  console.log('Server is running on http://localhost:3000');
});

export default app;