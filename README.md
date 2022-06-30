QtCellInk
=========

Public Qt extensions by CELLINK AB.

Before submitting or reviewing a PR, please read our [Contributing Guidelines](CONTRIBUTING.md)

## Porting to Qt5.15.x
**Note: Currently there is a workaround implemented which does not require below steps**

When using a Qt version >= 5.15.x, the following must be taken in consideration:
- **qtdeclarative** module must be rebuilt with the **qml-object-model** feature. To accomplish this, before building Qt, the **configure** command must include the option **-feature-qml-object-model**, together with the other preffered options.  
- Add the **Q_QMLMODELS_PRIVATE_EXPORT** macro to **QQmlObjectModelAttached** class. To do this, you must edit the qqmlobjectmodel_p.h header which is found in: **"your Qt5.15.x dir"/5.15.x/Src/qtdeclarative/src/qmlmodels** directory, and add the **Q_QMLMODELS_PRIVATE_EXPORT** macro in front of the **QQmlObjectModelAttached** class like so:

  `class Q_QMLMODELS_PRIVATE_EXPORT QQmlObjectModelAttached : public QObject`
  
- Rebuild the **qtdeclarative** module
