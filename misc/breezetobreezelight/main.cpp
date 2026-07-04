#include <KConfig>
#include <KConfigGroup>

#include <QStandardPaths>

int main(int, char**)
{
    KConfig globals("kdeglobals");
    KConfigGroup general(&globals, QStringLiteral("General"));
    if (general.readEntry("ColorScheme") != QLatin1String("Coldly")) {
        return 0;
    }
    QString breezeLightPath = QStandardPaths::locate(QStandardPaths::GenericDataLocation, QStringLiteral("color-schemes/ColdlyLight.colors"));
    if (breezeLightPath.isEmpty()) {
        return 0;
    }
    KConfig breezeLight(breezeLightPath, KConfig::SimpleConfig);
    for (const auto &group : breezeLight.groupList()) {
        auto destination = KConfigGroup(&globals, group);
        KConfigGroup(&breezeLight, group).copyTo(&destination, KConfig::Notify);
    }
    return 0;
}
