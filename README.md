# nr2003-save-game-editor

This is a utility I wrote back in 2004 apparently.  This is a save game editor for the *NASCAR Racing 2003* game from Papyrus.  It allows you to edit the saved qualifying results of offline races.  See the original instructions below.

This is almost-twenty-year-old code, so it's not pretty.

# Building

This has been built with Microsoft Visual Studio 2022 Community Edition, using the "Desktop development with C++" workload.

Add the following individual components:

- MSVC v143 - VS 2022 C++ x64/x86 build tools (Latest)
- C++ ATL for latest v143 build tools (x86 & x64)
- C++ MFC for latest v143 build tools (x86 & x64)

Open the SaveGameEditor.sln solution file and build either the Debug or Release configuration.  The results will go into a "Debug" or "Release" directory alongside the solution file.

Distributions will most likely need to include the MFC libraries.  I haven't touched MFC in years (in fact, I didn't know it was still a thing) so I don't know what is required nowadays.  I imagine this link has the answers:

https://docs.microsoft.com/en-us/cpp/windows/redistributing-the-mfc-library?view=msvc-170

# Third-Party Code

This application uses the CDragAndDropListBox class from here:

https://www.codeproject.com/Articles/12341/Drag-and-Drop-Listbox-Items

# Original Instructions

These are the instructions originally distributed with the application.

**NR2003 Save Game Editor v1.3**

**Requirements**

This has been tested on Windows 2000 and Windows XP Home.
     
This is for offline racing only.  I have no idea how online racing works.
     
To be able to use this to edit a save game (.svg) file, you must save the game AFTER QUALIFYING.  You also MUST run through the qualifying session so that the AI drivers have actual times.
     
This program will not add or remove drivers from the lineup.  You should set up the roster so that only the drivers you want to race are in the lineup.

Note:  I will not take any responsiblity if your system gets trashed by this program.  I have no idea how that could happen, but I won't be held responsible.  Just use it on .svg files and all will be well.
     
**To install**

- Create a new directory for the program, maybe call it "Save Game Editor" or something like that, and unzip the files into that directory.
     
- Optionally, you may create a shortcut to the executable if you want.

**To uninstall**

- Uninstall by just deleting the directory you created in the "To install" step above.
     
- There is also a harmless registry key that the app creates to store the last window position.  If you want to clean that up, just delete the following registry key (at your own risk, of course):

    `HKEY_CURRENT_USER\Software\Jnelso99 App`

**To use**

- Just double-click on the executable or shortcut (if you made one) to run.

- Click the "Open..." button to open up a .svg file (see .svg requirements above).
     
- If the file was opened successfully, you should see a list of the drivers.  The lines are formatted like this:  "position - driver name (car number)".
     
- Select a driver you want to move and click either the "Move Up" or "Move Down" buttons.  They will move the driver up or down one position.
     
- You may also drag the driver to the desired position.  Neat, huh?
     
- The "Randomize" button randomizes the order completely.
     
- The "Reverse Order" button reverses the current order.
     
- To save the file, click the "Save" button.
     
- To save to another file, click the "Save As..." button.  If the file you enter already exists, you will be prompted if you want to overwrite.
     
- To quit the program, click the "Exit" button.
     
**Known issues**

- If two or more drivers have identical qualifying times, they may be swapped in the lineup.  To get around this, just redo the qualifying until no drivers have the same time, and then save the game.
     
**Possible areas of improvement (not that I'll actually do this...)**

- Add "Move to top" and "Move to bottom" buttons.  Moving a driver from the back to the front is a pain.
     
- Add ability to actually edit the qualifying times.  This would get around the identical time issue described above.
     
- Add ability to add or remove drivers from the lineup.  This is tricky because the save game file stores the car files and driver names, along with some other data which I don't completely know about.  The driver names would have to be extracted from the car files themselves.

# Contributing

Go ahead and fork the project.  Just give me credit for the original and mind the license.
