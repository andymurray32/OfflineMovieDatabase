

#ifndef MOVIE_H
#define MOVIE_H

#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <sstream>

using namespace std;

#include "MovieLink.h"

class Movie {
private:
    string title;
    unsigned int year;
    MovieCertificate *cert;
    vector<MovieGenre *> genre;
    unsigned int duration;
    MovieDatabase *parent;
    unsigned int reviewCount;
    unsigned int reviewPoints;
public:
    friend class MovieDatabase;

    friend class Movie;

    // constructors / deconstructors

    Movie();

    Movie(Movie *cloneMovie, MovieDatabase *newParent);

    Movie(MovieDatabase *newParent);

    // setters
    void setCert(MovieCertificate *newCert);

    void setCert(string newCertName);

    void setTitle(string newTitle);

    void setYear(unsigned int newYear);

    void setDuration(unsigned int newDuration);

    void addGenre(MovieGenre *newGenre);

    void addGenre(string newGenreName);

    void removeGenre(MovieGenre *oldGenre);

    void setReviewCount(unsigned int newReviewCount); //for future reviews
    void setReviewPoints(unsigned int newReviewPoints);

    void setReviewAverage(double newReviewAverage);

    void addScore(int score);


    // getters
    MovieDatabase *getParent() const;

    string getCert() const;

    string getTitle() const;

    unsigned int getYear() const;

    unsigned int getDuration() const;

    //check for genre and cert
    bool hasGenre(MovieGenre *findGenre);

    bool hasCert(MovieCertificate *findCert);

    //returns a string of the multiple genres
    string getGenresStr() const;

    //number of genres
    int getGenreCount() const;

    //when reviews are added to the database
    unsigned int getReviewCount() const;

    double getAverageScore() const;

};


//Stream based I/O using operator overloading
inline std::ostream &operator<<(ostream &os, Movie &m) {
    return os << '"' << m.getTitle() << '"' << ',' << m.getYear() << ',' <<
              '"' << m.getCert() << '"' << ',' << '"' << m.getGenresStr() <<
              '"' << ',' << m.getDuration() << ',' << m.getAverageScore();
};


inline std::stringstream &operator>>(stringstream &s1, Movie *m1) {
    string discard;
    string Title, Year, Cert, Genres, Duration, AverageReview;
    // getting the corresponding values for their variable
    getline(s1, discard, '"');
    getline(s1, Title, '"');
    getline(s1, discard, ',');
    getline(s1, Year, ',');
    getline(s1, discard, '"'); //due to "" in stream
    getline(s1, Cert, '"');
    getline(s1, discard, '"');
    getline(s1, Genres, '"');
    getline(s1, discard, ',');
    getline(s1, Duration, ',');
    getline(s1, AverageReview, ',');

    // setting
    m1->setTitle(Title);
    m1->setYear((unsigned int) stoi(Year));
    m1->setCert(Cert);
    m1->setDuration((unsigned int) stoi(Duration));
    m1->setReviewAverage(stoi(AverageReview));
    m1->setCert(Cert);


    // add the genres
    stringstream ssGenres(Genres);
    string Genre;

    while (ssGenres) {
        getline(ssGenres, Genre, '/');
        m1->addGenre(Genre);
    }
    return s1;
};


//inspired from https://stackoverflow.com/questions/37608526/not-declared-in-scope-friend-comparator-class-for-priority-queue-c
//Handling the comparison of the films using methods in database
inline bool operator<(const Movie &a, const Movie &b) {
    return CompareFilm::movieLT(a, b, *a.getParent());
}

inline bool operator>(const Movie &a, const Movie &b) {
    return CompareFilm::movieGT(a, b, *a.getParent());
}

inline bool operator==(const Movie &a, const Movie &b) {
    return CompareFilm::movieEQ(a, b, *a.getParent());
}

inline bool operator!=(const Movie &a, const Movie &b) {
    return !CompareFilm::movieEQ(a, b, *a.getParent());
}

inline bool operator<=(const Movie &a, const Movie &b) {
    return !CompareFilm::movieGT(a, b, *a.getParent());
}

inline bool operator>=(const Movie &a, const Movie &b) {
    return !CompareFilm::movieLT(a, b, *a.getParent());
}


#endif /* MOVIE_H */
