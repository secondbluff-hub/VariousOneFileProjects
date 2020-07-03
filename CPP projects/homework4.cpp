#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person {
public:
    Person(const string& name, const string& type) : Name(name), Type(type) {}

    void IsDoing(const string& str) const {
        cout << Type << ": " << Name << str << endl;
    }

    virtual void Walk(const string& destination) const {
        IsDoing(" walks to: " + destination);
    }

    string GetName() const {
        return Name;
    }

    string GetType() const {
        return Type;
    }

protected:
    const string Name;
    const string Type;
};


class Student : public Person {
public:

    Student(const string& name, const string& favouriteSong) : Person(name, "Student"), FavouriteSong(favouriteSong) {}

    void Learn() const {
        IsDoing(" learns");
    }

    void SingSong() const {
        IsDoing(" sings a song: " + FavouriteSong);
    }

    void Walk(const string& destination) const override {
        Person::Walk(destination);
        this->SingSong();
    }

    string GetFavoriteSong() const {
        return FavouriteSong;
    }

 private:
     const string FavouriteSong;
};


class Teacher : public Person {
public:

    Teacher(const string& name, const string& subject) : Person(name, "Teacher"), Subject(subject) {}

    void Teach() {
        IsDoing(" teaches: " + Subject);
    }

    string GetSubject() const {
        return Subject;
    }

private:
     const string Subject;
};


class Policeman : public Person {
public:
    Policeman(const string& name) : Person(name, "Policeman") {}

    void Check(const Person& p) {
        IsDoing(" checks " + p.GetType() + ". " + p.GetType() + "'s name is: " + p.GetName());
    }
};

void VisitPlaces(const Person& p, const vector<string>& places) {
    for (auto place : places) {
        p.Walk(place);
    }
}

int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    t.Teach();
    s.SingSong();
    s.Learn();
    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}