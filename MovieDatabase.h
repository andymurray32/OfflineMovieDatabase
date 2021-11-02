

#ifndef MOVIEDATABASE_H
#define MOVIEDATABASE_H

#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <sstream>

using namespace std;


#include "Movie.h"



class MovieDatabase {
private:
    std::vector<Movie> filmDB;
public:
    enum SortFields {
        title, year, certificate, genre, duration, average_rating, title_length
    };
    std::vector<string> titles;
    std::vector<Movie *> movies;
    std::vector<MovieCertificate *> certificates;
    std::vector<MovieGenre *> genres;
    SortFields sortField;
    bool sortDesc;

public:
    friend class MovieDatabase;

    //queries
    bool addMovie(Movie *newMovie);

    bool addMovie(stringstream &CSVlinestream);

    Movie *getIndex(int i) const;

    SortFields getSortField() const;

    void sortDatabase(SortFields field, bool desc);

    MovieCertificate *getCert(string certStr);

    MovieGenre *getGenre(string genreStr);

    MovieDatabase *genreList(MovieGenre *findGenre);

    MovieDatabase *certList(MovieCertificate *findCert);

    long count() const;

    string movieString(Movie &mp) const;

    //constructor
    MovieDatabase();
};

inline std::ifstream &operator>>(ifstream &is, MovieDatabase &filmDB) {
    string lineString;
    while (getline(is, lineString)) {
        stringstream lineStream(lineString);
        filmDB.addMovie(lineStream);
    }
    cout << filmDB.count() << " films got added to database\n";
    return is;
}

//reading and printing moviestring
inline std::ofstream &operator<<(std::ofstream &os, const MovieDatabase &filmDB) {
    int a = filmDB.count();
    if (a < 1) {
        return os;
    }

    os << filmDB.movieString(*filmDB.getIndex(0));
    int i = 0;
    while (++i < a) {
        os << "\r\n" << filmDB.movieString(*filmDB.getIndex(i));

    }
    return os;
}

inline std::ostream &operator<<(std::ostream &os, const MovieDatabase &filmDB) {
    int b = filmDB.count();
    if (b < 1) {
        return os;
    }
    os << filmDB.movieString(*filmDB.getIndex(0));
    int i = 0;
    while (++i < b) {
        os << "\r\n" << filmDB.movieString(*filmDB.getIndex(i));
    }
    return os;
}

#endif /* MOVIEDATABASE_H */
