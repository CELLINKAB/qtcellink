# CellInk Widgets Plugin

## One time installation

Install/Copy to your current Qt kit's widgets plugin directory in <build>\src\plugins\ui\celllinkwidgets:

### Linux

```bash
make install
```

If your Qt installation directory is not writeable, you need to copy these somewhere else
and/or modify some suitable environment variable and add the directory so Qt Designer will find it.

### Windows

```bash
C:\Qt\Tools\QtCreator\bin\jom.exe -f Makefile.Release install
```

Then you can launch <QtDir>\bin\designer and design away!

**NOTE** Qt Creator may have a different plugins directory than designer, so check the path to QtCreator(.exe) and adapt.

## Continuous development with Qt Creator

Add a custom make build target to the release build for the Qt kit you are developing with:

```bash
install -f %{buildDir}\src\plugins\ui\cellinkwidgets\Makefile.Release
```

**NOTE** You need to close Qt Designer between builds as it locks the DLL when it is loaded.
