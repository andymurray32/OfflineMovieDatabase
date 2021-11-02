/* 

 */
#include "MovieDatabase.h"

//Constructor for db
MovieDatabase::MovieDatabase() {
    sortDesc = false;
    sortField = title; // automatically set for alphabetical
}

//return enum for sortfield
MovieDatabase::SortFields MovieDatabase::getSortField() const {
    return MovieDatabase::sortField;
};


//creating movie database for genre+ certificate
MovieDatabase *MovieDatabase::genreList(MovieGenre *findGenre) {
    MovieDatabase *gDB = new MovieDatabase();
    gDB->genres = this->genres;
    int i = 0;
    int a = movies.size();
    Movie *r = movies[0];
    while (++i < a) {
        if (movies[i]->hasGenre(findGenre)) {
            /*
             * Movies have to be cloned, as they need to point to the
             * new Movie Database to get sort settings
             */
            Movie *clone = new Movie(movies[i], gDB);
            gDB->addMovie(clone);
        }
    }
    return gDB;
};

MovieDatabase *MovieDatabase::certList(MovieCertificate *findCert) {
    MovieDatabase *cDB = new MovieDatabase();
    cDB->certificates = this->certificates;
    int i = 0;
    int b = movies.size();
    Movie *r = movies[0];
    while (++i < b) {
        if (movies[i]->hasCert(findCert)) {
            /*
             * Movies have to be cloned, as they need to point to the
             * new Movie Database to get sort settings
             */
            Movie *clone = new Movie(movies[i], cDB);
            cDB->addMovie(clone);
        }
    }
    return cDB;
};

//return number of movies in db
long MovieDatabase::count() const {
    return movies.size();
};

//return movie as string
string MovieDatabase::movieString(Movie &mp) const {
    stringstream s2;
    s2 << mp;
    return s2.str();
}
//getters//////////

// getting pointer for the cert  and adds to vector if its a new certificate
MovieCertificate *MovieDatabase::getCert(string certStr) {
    int c = (this->certificates).size();
    int i = -1;
    while (++i < c) {
        if (*((this->certificates)[i]) == certStr) {
            return ((this->certificates)[i]);
        }
    }
    MovieCertificate *newCert = new MovieCertificate(certStr);
    (this->certificates).push_back(newCert);// adds to end of vector
    return newCert;

};

//getting pointer for genre, and add if adds it to vector if new so new genres can be easily added
MovieGenre *MovieDatabase::getGenre(string genreStr) {
    int d = (this->genres).size();
    int i = -1;
    while (++i < d) {
        if (*((this->genres)[i]) == genreStr) {
            return (this->genres[i]);
        }
    }
    MovieGenre *newGenre = new MovieGenre(genreStr);
    (this->genres).push_back(newGenre); //adds to end of vector
    return newGenre;
};

//gets the pointer to the certificate from the db and string (certficate)
MovieCertificate *MovieDatabaseLink::getCert(string certStr, MovieDatabase &mdb) {
    return mdb.getCert(certStr);
};

//gets the pointer to the genre from the db and string (genre)
MovieGenre *MovieDatabaseLink::getGenre(string genreStr, MovieDatabase &mdb) {
    return mdb.getGenre(genreStr);
};

//get movie pointer at index
Movie *MovieDatabase::getIndex(int i) const {
    if (i >= 0 && i < movies.size()) {
        return movies[i];
    } else if (i < 0) {
        return movies[0];
    }
    return movies[movies.size() - 1];
};


//true if movie in db,add it if not
bool MovieDatabase::addMovie(Movie *newMovie) {
    int i = -1;
    int e = titles.size();
    while (++i < e) {
        if (newMovie->getTitle() == titles[i]) {
            return false;
        }
    }
    (this->titles).push_back(newMovie->title); //add to title vector
    (this->movies).push_back(newMovie); //add to movies
    return true;
};

//true if movies added from CSV
bool MovieDatabase::addMovie(stringstream &CSVlinestream) {
    Movie *newMovie = new Movie(this);
    CSVlinestream >> newMovie;
    return this->addMovie(newMovie);
};


bool compareMovie(Movie *a, Movie *b) { return (*a < *b); }

bool compareMovieDesc(Movie *a, Movie *b) { return (*b < *a); }

//sorts database
void MovieDatabase::sortDatabase(MovieDatabase::SortFields field, bool desc) {
    sortField = field;
    sortDesc = desc;
    if (sortDesc) {
        sort(movies.begin(), movies.end(), compareMovieDesc);
    } else {
        sort(movies.begin(), movies.end(), compareMovie);
    }
};


//compares films handling whether films are < == or < each other
bool CompareFilm::movieLT(const Movie &a, const Movie &b,
                          const MovieDatabase &db) {
    switch (db.getSortField()) {
        case MovieDatabase::SortFields::year:
            return a.getYear() < b.getYear();
            break;
        case MovieDatabase::SortFields::genre:
            return a.getGenreCount() < b.getGenreCount();
            break;
        case MovieDatabase::SortFields::certificate:
            return a.getCert() < b.getCert();
            break;
        case MovieDatabase::SortFields::duration:
            return a.getDuration() < b.getDuration();
            break;
        case MovieDatabase::SortFields::average_rating:
            return a.getAverageScore() < b.getAverageScore();
            break;
        case MovieDatabase::SortFields::title_length:
            return a.getTitle().length() < b.getTitle().length();
            break;
        case MovieDatabase::SortFields::title:
        default:
            return a.getTitle() < b.getTitle();
            break;
    }
}

bool CompareFilm::movieGT(const Movie &b, const Movie &a,
                          const MovieDatabase &db) {
    switch (db.getSortField()) {
        case MovieDatabase::SortFields::year:
            return a.getYear() > b.getYear();
            break;
        case MovieDatabase::SortFields::genre:
            return a.getGenreCount() > b.getGenreCount();
            break;
        case MovieDatabase::SortFields::certificate:
            return a.getCert() > b.getCert();
            break;
        case MovieDatabase::SortFields::duration:
            return a.getDuration() > b.getDuration();
            break;
        case MovieDatabase::SortFields::average_rating:
            return a.getAverageScore() > b.getAverageScore();
            break;
        case MovieDatabase::SortFields::title_length:
            return a.getTitle().length() > b.getTitle().length();
            break;
        case MovieDatabase::SortFields::title:
        default:
            return a.getTitle() > b.getTitle();
            break;
    }
}


bool CompareFilm::movieEQ(const Movie &a, const Movie &b,
                          const MovieDatabase &db) {
    switch (db.getSortField()) {
        case MovieDatabase::SortFields::year:
            return a.getYear() == b.getYear();
            break;
        case MovieDatabase::SortFields::genre:
            return a.getGenreCount() == b.getGenreCount();
            break;
        case MovieDatabase::SortFields::certificate:
            return a.getCert() == b.getCert();
            break;
        case MovieDatabase::SortFields::duration:
            return a.getDuration() == b.getDuration();
            break;
        case MovieDatabase::SortFields::average_rating:
            return a.getAverageScore() == b.getAverageScore();
            break;
        case MovieDatabase::SortFields::title_length:
            return a.getTitle().length() == b.getTitle().length();
            break;
        case MovieDatabase::SortFields::title:
        default:
            return a.getTitle() == b.getTitle();
            break;
    }
}





 

 
 


