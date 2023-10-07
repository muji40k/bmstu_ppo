#ifndef _APP_H_
#define _APP_H_

class App
{
    public:
        virtual ~App(void) = default;
        virtual int run(void) = 0;
};

#endif

