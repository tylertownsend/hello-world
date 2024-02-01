// See https://aka.ms/new-console-template for more information
using System;
using System.CommandLine;
using Terminal.Gui;

using System.CommandLine;
using Terminal.Gui;
using NStack;
using System.ComponentModel;


class SecondStepState
{
    public Label ButtonLbl { get; set; }
    public Label Lbl { get; set; }
    public TextField FirstNameField { get; set; }
    public TextField LastNameField { get; set; }
    public CheckBox ThirdStepEnabledCeckBox { get; set; }
}

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

        try
        {
            int width = 80;
            int height = 20;

            if (width < 1 || height < 1)
            {
                MessageBox.ErrorQuery("Nope", "Height and width must be greater than 0 (much bigger)", "Ok");
                return;
            }

            // actionLabel.Text = ustring.Empty;

            var wizard = new Wizard("Wizard Scenario")
            {
                Width = width,
                Height = height
            };

            // wizard.MovingBack += (args) =>
            // {
            //     //args.Cancel = true;
            //     actionLabel.Text = "Moving Back";
            // };

            // wizard.MovingNext += (args) =>
            // {
            //     //args.Cancel = true;
            //     actionLabel.Text = "Moving Next";
            // };

            // wizard.Finished += (args) =>
            // {
            //     //args.Cancel = true;
            //     actionLabel.Text = "Finished";
            // };

            // wizard.Cancelled += (args) =>
            // {
            //     //args.Cancel = true;
            //     actionLabel.Text = "Cancelled";
            // };

            AddFirstStep(wizard);

            // ---------------------------
            // Add 2nd step
            // ---------------------------

            var buttonLbl = new Label() { Text = "Second Step Button: ", X = 1, Y = 1 };
            var lbl = new Label() { Text = "First Name: ", X = 1, Y = Pos.Bottom(buttonLbl) };
            var firstNameField = new TextField() { Text = "Number", Width = 30, X = Pos.Right(lbl), Y = Pos.Top(lbl) };
            var lastNameField = new TextField() { Text = "Six", Width = 30, X = Pos.Right(lbl), Y = Pos.Top(lbl) };
            var thirdStepEnabledCeckBox = new CheckBox() { Text = "Enable Step _3", Checked = false, X = Pos.Left(lastNameField), Y = Pos.Bottom(lastNameField) };

            var secondStepState = new SecondStepState()
            {
                ButtonLbl = buttonLbl,
                Lbl = lbl,
                FirstNameField = firstNameField,
                LastNameField = lastNameField,
                ThirdStepEnabledCeckBox = thirdStepEnabledCeckBox
            };
            AddSecondStep(wizard, secondStepState);
            AddThirdStep(wizard);
            AddFourthStep(wizard);
            AddFifthStep(wizard);

            win.Add(wizard);
            Application.Run();
        }
        catch (FormatException)
        {
        }

        // Create and show the application
        Application.Shutdown();
    }

    private static void AddFirstStep(Wizard wizard)
    {
        var firstStep = new Wizard.WizardStep("End User License Agreement");
        firstStep.NextButtonText = "Accept!";
        firstStep.HelpText = "This is the End User License Agreement.\n\n\n\n\n\nThis is a test of the emergency broadcast system. This is a test of the emergency broadcast system.\nThis is a test of the emergency broadcast system.\n\n\nThis is a test of the emergency broadcast system.\n\nThis is a test of the emergency broadcast system.\n\n\n\nThe end of the EULA.";
        wizard.AddStep(firstStep);
    }

    private static void AddSecondStep(Wizard wizard, SecondStepState state)
    {
        var secondStep = new Wizard.WizardStep("Second Step");
        wizard.AddStep(secondStep);
        secondStep.HelpText = "This is the help text for the Second Step.\n\nPress the button to change the Title.\n\nIf First Name is empty the step will prevent moving to the next step.";

        var button = new Button()
        {
            Text = "Press Me to Rename Step",
            X = Pos.Right(state.ButtonLbl),
            Y = Pos.Top(state.ButtonLbl)
        };
        button.Clicked += () =>
        {
            secondStep.Title = "2nd Step";
            MessageBox.Query("Wizard Scenario", "This Wizard Step's title was changed to '2nd Step'");
        };
        secondStep.Add(state.ButtonLbl, button);
        secondStep.Add(state.Lbl, state.FirstNameField);
        state.Lbl = new Label() { Text = "Last Name:  ", X = 1, Y = Pos.Bottom(state.Lbl) };
        secondStep.Add(state.Lbl, state.LastNameField);
        secondStep.Add(state.ThirdStepEnabledCeckBox);

        // Add a frame 
        var frame = new FrameView($"A Broken Frame (by Depeche Mode)")
        {
            X = 0,
            Y = Pos.Bottom(state.ThirdStepEnabledCeckBox) + 2,
            Width = Dim.Fill(),
            Height = 4
        };
        frame.Add(new TextField("This is a TextField inside of the frame."));
        secondStep.Add(frame);
        wizard.StepChanging += (args) =>
        {
            if (args.OldStep == secondStep && state.FirstNameField.Text.IsEmpty)
            {
                args.Cancel = true;
                var btn = MessageBox.ErrorQuery("Second Step", "You must enter a First Name to continue", "Ok");
            }
        };
    }

    private static void AddThirdStep(Wizard wizard)
    {
        var thirdStep = new Wizard.WizardStep("Third Step (Optional)");
        wizard.AddStep(thirdStep);
        thirdStep.HelpText = "This is step is optional (WizardStep.Enabled = false). Enable it with the checkbox in Step 2.";
        var step3Label = new Label()
        {
            Text = "This step is optional.",
            X = 0,
            Y = 0
        };
        thirdStep.Add(step3Label);
        var progLbl = new Label() { Text = "Third Step ProgressBar: ", X = 1, Y = 10 };
        var progressBar = new ProgressBar()
        {
            X = Pos.Right(progLbl),
            Y = Pos.Top(progLbl),
            Width = 40,
            Fraction = 0.42F
        };
        thirdStep.Add(progLbl, progressBar);
        // thirdStep.Enabled = thirdStepEnabledCeckBox.Checked;
        // thirdStepEnabledCeckBox.Toggled += (args) =>
        // {
        //     thirdStep.Enabled = thirdStepEnabledCeckBox.Checked;
        // };
    }

    private static void AddFourthStep(Wizard wizard)
    {
        // Add 4th step
        var fourthStep = new Wizard.WizardStep("Step Four");
        wizard.AddStep(fourthStep);
        var someText = new TextView()
        {
            Text = "This step (Step Four) shows how to show/hide the Help pane. The step contains this TextView (but it's hard to tell it's a TextView because of Issue #1800).",
            X = 0,
            Y = 0,
            Width = Dim.Fill(),
            Height = Dim.Fill(1),
            WordWrap = true,
            AllowsTab = false,
            ColorScheme = Colors.Base
        };
        var help = "This is helpful.";
        fourthStep.Add(someText);
        var hideHelpBtn = new Button()
        {
            Text = "Press me to show/hide help",
            X = Pos.Center(),
            Y = Pos.AnchorEnd(1)
        };
        hideHelpBtn.Clicked += () =>
        {
            if (fourthStep.HelpText.Length > 0)
            {
                fourthStep.HelpText = ustring.Empty;
            }
            else
            {
                fourthStep.HelpText = help;
            }
        };
        fourthStep.Add(hideHelpBtn);
        fourthStep.NextButtonText = "Go To Last Step";
        var scrollBar = new ScrollBarView(someText, true);

        scrollBar.ChangedPosition += () =>
        {
            someText.TopRow = scrollBar.Position;
            if (someText.TopRow != scrollBar.Position)
            {
                scrollBar.Position = someText.TopRow;
            }
            someText.SetNeedsDisplay();
        };

        scrollBar.VisibleChanged += () =>
        {
            if (scrollBar.Visible && someText.RightOffset == 0)
            {
                someText.RightOffset = 1;
            }
            else if (!scrollBar.Visible && someText.RightOffset == 1)
            {
                someText.RightOffset = 0;
            }
        };

        someText.DrawContent += (e) =>
        {
            scrollBar.Size = someText.Lines;
            scrollBar.Position = someText.TopRow;
            if (scrollBar.OtherScrollBarView != null)
            {
                scrollBar.OtherScrollBarView.Size = someText.Maxlength;
                scrollBar.OtherScrollBarView.Position = someText.LeftColumn;
            }
            scrollBar.LayoutSubviews();
            scrollBar.Refresh();
        };
        fourthStep.Add(scrollBar);
    }

    private static void AddFifthStep(Wizard wizard)
    {
        // Add last step
        var lastStep = new Wizard.WizardStep("The last step");
        wizard.AddStep(lastStep);
        lastStep.HelpText = "The wizard is complete!\n\nPress the Finish button to continue.\n\nPressing ESC will cancel the wizard.";
        var finalFinalStepEnabledCeckBox = new CheckBox() { Text = "Enable _Final Final Step", Checked = false, X = 0, Y = 1 };
        lastStep.Add(finalFinalStepEnabledCeckBox);
        lastStep.NextButtonText = "Finish";
    }
}