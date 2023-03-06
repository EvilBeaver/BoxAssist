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

    variant_t calculate(const variant_t &input, const variant_t &sum);
    variant_t test(const variant_t &input);
};


#endif //SAMPLEADDIN_BOXASSIST_H
