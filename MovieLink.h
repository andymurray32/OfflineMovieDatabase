
#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>

#ifndef MOVIELINK_H
#define MOVIELINK_H

//this header was created due to issues accessing methods between films and database.
//I was unable to make my code more modular without my programming not working
//had to create classes to update the db with the parent db
class Movie;

class MovieDatabase;

using namespace std;

//made to update with changes to parent db
class MovieCertificate {
private:
    string name;
public:
    string toString() const {
        return name;
    };

    MovieCertificate(string newName) {
        name = newName;
    };
};

inline bool operator==(const MovieCertificate &a, const string &b) {
    return (a.toString()) == b;
}

inline bool operator!=(const MovieCertificate &a, const string &b) {
    return !(a == b);
}

//made to update with changes to parent db
class MovieGenre {
private:
    string name;
public:
    string toString() const {
        return name;
    };

    MovieGenre(string newName) {
        name = newName;
    };
};

inline bool operator==(const MovieGenre &a, const string &b) {
    return (a.toString()) == b;
}

inline bool operator!=(const MovieGenre &a, const string &b) {
    return !(a == b);
}

//films compared based on settings from parent db
//compare to a sorted parent db
class CompareFilm {
public:
    static bool movieLT(const Movie &a, const Movie &b, const MovieDatabase &c);

    static bool movieGT(const Movie &a, const Movie &b, const MovieDatabase &c);

    static bool movieEQ(const Movie &a, const Movie &b, const MovieDatabase &c);
};

//link movie and db for cert and genre
class MovieDatabaseLink {
public:
    static MovieCertificate *getCert(string certStr, MovieDatabase &mdb);

    static MovieGenre *getGenre(string certStr, MovieDatabase &mdb);
};


#endif /* MOVIELINK_H */
