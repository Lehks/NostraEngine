#ifndef NOE_CORE_UPDATABLE_HPP
#def NOE_CORE_UPDATABLE_HPP

class Updatable{
public:
    virtual void earlyUpdate() = 0;
    virtual void update() = 0;
    virtual void lateUpdate() = 0;
};



#endif