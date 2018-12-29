#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include <QString>

class PluginInterface
{
public:
    virtual ~PluginInterface() {}
    virtual QString getName();
    virtual void initialize();
};

Q_DECLARE_INTERFACE(PluginInterface, "eu.murda.desktopclock.PluginInterface")

#endif // PLUGININTERFACE_H
