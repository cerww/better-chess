#ifndef IGAMESCREEN_H
#define IGAMESCREEN_H
#include <vector>

class iGameScreen{    
    public:        
    virtual void draw() = 0;
    virtual std::pair<bool,std::vector<int>>update() = 0;
};

#endif // IGAMESCREEN_H
