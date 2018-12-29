# Desktop Clock

Customizable desktop clock widget written in Qt5 framework.

## Building Installer with Qt Creator (Windows)

To get started make sure you have all the following requirements and
after that open desktop-clock project with Qt Creator.

### Requirements

* Qt 5
* Qt Creator
* Qt Installer Framework 3

### Build Settings

You can monitor build process by keeping `Compile Output` (Alt + 4) tab open in Qt Creator,
it is very useful in case something goes wrong and you need to see error messages.

* Start by navigating to `Projects` and make sure that `Active Project` is set to `desktop-clock` in side menu.
* Under the `Build Settings` header there is dropdown with label `Edit build configuration`,
change this to be `release`.
* Next thing to do is to disable/untick `Shadow build` option,
by doing so Qt Creator will use project folder as destination folder.

Now you are ready to start adding Custom Process Steps,
you can add them by clicking caret in dropdown that has text `Add Build Step` inside,
after dropdown opens select `Custom Process Step`, this gives you a new form to fill up.

#### Custom Process Step (windeployqt.exe)

* Command

    For field with label `Command` first thing to do is to locate `windeployqt.exe` on your filesystem.
    If this binary exists in your environment's PATH variable then
    you can just enter the name of the binary without any leading directories.

    This binary is usually located at `{Qt Directory}\{Qt Version}\{Compiler Directory}\bin\windeployqt.exe`

* Arguments

    For field with label `Arguments` enter following value:
    `installer\packages\eu.murda.desktopclock\data\desktop-clock.exe`

* Working directory

    For field with label `Working directory` make sure that value is set to `%{buildDir}`, it usually is by default.

#### Custom Process Step (binarycreator.exe)

* Command

    For field with label `Command` first thing to do is to locate `binarycreator.exe` on your filesystem.
    If this binary exists in your environment's PATH variable then
    you can just enter name of the binary without any leading directories.

    This binary is usually located at `{Qt Directory}\Tools\QtInstallerFramework\3.{*}\bin\binarycreator.exe`

* Arguments

    For field with label `Arguments` enter following value:
    `--offline-only -c installer\config\config.xml -p installer\packages installer\DesktopClockInstaller.exe`

* Working directory

    For field with label `Working directory` make sure that value is set to `%{buildDir}`, it usually is by default.

#### Custom Process Step (upx.exe) [OPTIONAL]

This step is completely optional, but by adding this step your final installer file will be much smaller in size.

You can download `upx.exe` binary from here: [https://upx.github.io](https://upx.github.io)

* Command

    For field with label `Command` first thing to do is to locate `upx.exe` on your filesystem.
    If this binary exists in your environment's PATH variable the
    you can just enter name of the binary without any leading directories.

* Arguments

    For field with label `Arguments` enter following value: `-9  installer\DesktopClockInstaller.exe`

* Working directory

    For field with label `Working directory` make sure that value is set to `%{buildDir}`, it usually is by default.

### Final Output

Final installer file will be located in directory `installer` and named `DesktopClockInstaller.exe`.
