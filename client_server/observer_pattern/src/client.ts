import { request } from 'http';
import * as fs from 'fs';

const options = {
  hostname: 'localhost',
  port: 3000,
  path: '/',
  method: 'GET'
};

const req = request(options, (response) => {
  console.log(`STATUS: ${response.statusCode}`);
  response.setEncoding('utf8');
  response.on('data', (chunk) => {
    console.log(`BODY: ${chunk}`);
  });
  response.on('end', () => {
    console.log('No more data in response.');
  });
});

req.on('error', (e) => {
  console.error(`problem with request: ${e.message}`);
});

// Write data to request body
req.end();