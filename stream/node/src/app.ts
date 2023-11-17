import { createServer, IncomingMessage, Server, ServerResponse } from 'http';

type Handler = (req: IncomingMessage, res: ServerResponse) => void;
type Route = {
  method: string;
  path: string;
  handler: Handler;
};

export class App {
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
