#ifndef PC_H
#define PC_H

class PC {
    private:
        int value;
    
    public:
        PC();
    
        int get() const;
        void set(int val);
        void increment();
        void decrement();
        void res();
        void add(int val);
        bool setsafe(int val);
        void rollback(int val);
        
    };

#endif // PC_H