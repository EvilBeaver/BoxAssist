//
// Created by antonina on 05.03.23.
//

#ifndef SAMPLEADDIN_BOXASSIST_H
#define SAMPLEADDIN_BOXASSIST_H

#include "Component.h"

class BoxAssist : public Component {
public:
    BoxAssist();

private:
    std::string extensionName() override;
};


#endif //SAMPLEADDIN_BOXASSIST_H
