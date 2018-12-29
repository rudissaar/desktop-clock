#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include <QString>

namespace rudissaar {
class PluginInterface
{
public:
    virtual ~PluginInterface() {}
    virtual QString getName();
    virtual void initialize();
};
}

Q_DECLARE_INTERFACE(rudissaar::PluginInterface, "eu.murda.desktopclock.PluginInterface")

#endif // PLUGININTERFACE_H
