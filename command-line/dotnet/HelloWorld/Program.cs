// See https://aka.ms/new-console-template for more information
using System;
using System.CommandLine;
using Terminal.Gui;

using System.CommandLine;
using Terminal.Gui;

class Program
{
    static int Main(string[] args)
    {
        // Define command line arguments using System.CommandLine
        var rootCommand = new RootCommand("My command line application with Terminal.Gui");

        // Setup the command to execute the RunGui method
        rootCommand.SetHandler(() =>
        {
            RunGui();
        });

        // Parse the incoming args and invoke the command
        return rootCommand.InvokeAsync(args).Result;
    }

    private static void RunGui()
    {
        // Initialize Terminal.Gui
        Application.Init();
        var top = Application.Top;

        // Create the window and add any controls here
        var win = new Window("Hello from Terminal.Gui")
        {
            X = 0,
            Y = 1, // Leave one row for the toplevel menu

            // By using Dim.Fill(), it will automatically resize without manual intervention
            Width = Dim.Fill(),
            Height = Dim.Fill()
        };
        top.Add(win);

        // Add a simple label
        var label = new Label("Welcome to your GUI app!")
        {
            X = Pos.Center(),
            Y = Pos.Center()
        };
        win.Add(label);

        // Create and show the application
        Application.Run();
    }
}