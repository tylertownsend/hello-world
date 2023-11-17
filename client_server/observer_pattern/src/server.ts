import { createServer, IncomingMessage, Server, ServerResponse } from 'http';

type Handler = (req: IncomingMessage, res: ServerResponse) => void;
type Route = {
  method: string;
  path: string;
  handler: Handler;
};

class App {
  private observers: Function[] = [];
  private routes: Route[] = [];

  public get(path: string, handler: Handler) {
    this.routes.push({ method: 'GET', path, handler });
  }

  public listen(port: number, callback: () => void) {
    const server = createServer((req, res) => {
      // Find a matching route
      this.handleSubscribers(req);
      this.handleRequests(req, res);
    });

    server.listen(port, callback);
  }

  public subscribe = (callback: Function): void => {
    this.observers.push(callback);
  }

  private handleSubscribers = (req: IncomingMessage): void => {
    this.observers.forEach((func) => {
      func(req);
    });
  }

  private handleRequests = (req: IncomingMessage, res: ServerResponse): void => {
    const matchedRoute = this.routes.find(route => {
      return route.path === req.url && route.method === req.method;
    });

    if (matchedRoute) {
      matchedRoute.handler(req, res);
    } else {
      res.statusCode = 404;
      res.end('404 Not Found');
    }
  }
}

const app = new App();

// Define routes for different endpoints
app.get('/', (req, res) => {
  res.end('Welcome to the homepage!');
});

app.get('/about', (req, res) => {
  res.end('About us page');
});

app.subscribe((request: IncomingMessage, response: ServerResponse) => {
  console.log('Received Request:', request.url);
})

app.listen(3000, () => {
  console.log('Server is running on http://localhost:3000');
});

export default app;