function Component()
{

}

Component.prototype.createOperations = function()
{
    component.createOperations();

    if (systemInfo.productType === "windows") {
        component.addOperation(
            "CreateShortcut",
            "@TargetDir@/desktop-clock.exe",
            "@StartMenuDir@/Desktop\ Clock.lnk",
            "workingDirectory=@TargetDir@",
            "iconPath=%SystemRoot%/system32/SHELL32.dll",
            "iconId=2",
            "description=Start Desktop Clock");

        component.addOperation(
            "CreateShortcut",
            "@TargetDir@/desktop-clock.exe",
            "@StartMenuDir@/../Startup/Desktop\ Clock.lnk",
            "workingDirectory=@TargetDir@",
            "iconPath=%SystemRoot%/system32/SHELL32.dll",
            "iconId=2",
            "description=Start Desktop Clock");
    }
}
