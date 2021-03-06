#include "VM/PNIEnv.h"

PNIEnv::PNIEnv(PkmVM* pvm) : pvm_(pvm) {}

void PNIEnv::loadClasses(PkmClasses* pclasses)
{
    classes_ = std::move(*pclasses);
}

pclass PNIEnv::findClass(const std::string& class_name)
{
    if (classes_.contains(class_name))
    {
        return &classes_[class_name];
    }

    return nullptr;
}

pmethodID PNIEnv::getMethodID(pclass cls, const std::string& met_name)
{
    if (cls->methods.contains(met_name))
    {
        return &cls->methods[met_name];
    }

    return nullptr;
}

void PNIEnv::callMethod(pclass, pmethodID)
{
}