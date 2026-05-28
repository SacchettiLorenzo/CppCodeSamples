#include <iostream>
#include <string>

class String {
public :
    String() = default;
    String(const char* string) {
        printf("Created!\n");
        m_Size = strlen(string);
        m_Data = new char[m_Size];
        memcpy(m_Data, string, m_Size);
    }

    //the copy constructor is needed to copy the m_Data of other into this m_Data
    String(const String& other) {
        printf("Copied!\n");
        m_Size = other.m_Size;
        m_Data = new char[m_Size];
        memcpy(m_Data, other.m_Data, m_Size);
    }

    String(String&& other) noexcept { //copy constructor with temporary String instance as parameter
        printf("Moved!\n");
        m_Size = other.m_Size;
        m_Data = other.m_Data; 

        other.m_Size = 0;
        other.m_Data = nullptr;
        //when the other String class instance will be deleted the m_Data will be not because we changed the pointer value
    }

    String& operator= (String&& other) noexcept { 

        if (this != &other) {
            printf("Moved! (=)\n");

            delete[] m_Data;

            m_Size = other.m_Size;
            m_Data = other.m_Data;

            other.m_Size = 0;
            other.m_Data = nullptr;

        }   

        return *this;
    }

    ~String() {
        printf("Destroyed!\n");
        delete m_Data;
    }

    void Print() {
        for (uint32_t i = 0; i < m_Size; i++){
            printf("%c", m_Data[i]);
        }
        printf("\n");
    }
private:
    char* m_Data;
    uint32_t m_Size;
};

class Entity {
public:
    Entity(const String& name) : m_Name(name) { //call the copy constructor of the String class
    }

    Entity(String&& name) : m_Name((String&&)name) { //call the move constructor of the String class because we are providing a temporary value (the cast is compulosory in order to call the move constructor)
    }

    //Entity(String&& name) : m_Name(std::move(name)) { //alterative using std::move
    //}

    void PrintName() {
        m_Name.Print();
    }
private:
    String m_Name;
};

int main()
{
    String src = "Test";
    //String dest = src; //this will copy the content

    //String _dest((String&&)src);//casting into a String temporary (rvalue reference) will call the move constructor
    //String __dest(std::move(src)); //more elegant way using std::move
    
    //String ___dest = (String&&)src; //call to the call the move constructor
    //String ____dest = std::move(src); //call the move constructor

    //String _____dest; 
    //_____dest.operator=(std::move(src)); //call to the call the assignemtn operator overloaded to move
    
    //
    //std::cin.get();
    //
    //Entity entity("Hello");
    //entity.PrintName();
    //
    //std::cin.get();
    //
    //Entity _entity = entity;
    //
    //std::cin.get();
    //
    //Entity __entity("Hello again");
    //__entity.PrintName();
}

//using a copy means that we need to allocate memory on the heap for the cration of String instance and then allocate some more meory for the copy


