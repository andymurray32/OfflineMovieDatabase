

#include "Movie.h"


//Construct for copying movie to another database to get a new list for certain parameters
Movie::Movie(Movie *cloneMovie, MovieDatabase *newParent) {
    this->parent = newParent;
    this->setTitle(cloneMovie->getTitle());
    this->setCert(cloneMovie->getCert());
    this->setYear(cloneMovie->getYear());
    this->setDuration(cloneMovie->getDuration());
    this->setReviewAverage(cloneMovie->getAverageScore());
    //as there is multiple genres in some cases
    int i = 0;
    int a = cloneMovie->getGenreCount();
    while (++i < a) {
        this->addGenre(cloneMovie->genre[i]);
    }
};

//movie created with reference to the parent database
Movie::Movie(MovieDatabase *newParent) {
    this->parent = newParent;
};

//Getters
//return pointer to parent db
MovieDatabase *Movie::getParent() const {
    return parent;
};

string Movie::getTitle() const {
    return this->title;
};

string Movie::getCert() const {
    return this->cert->toString();
};

unsigned int Movie::getYear() const {
    return this->year;
};

unsigned int Movie::getDuration() const {
    return this->duration;
};

//returns the multiple genres as string
string Movie::getGenresStr() const {
    int x = this->genre.size();
    if (x == 0) {
        return "";
    };
    stringstream s1;
    s1 << this->genre[0]->toString();
    if (x > 1) {
        int i = 0;
        while (++i < x) {
            s1 << '/' << this->genre[i]->toString();
        };
    };
    return s1.str();
};

//get number of genres a film has
int Movie::getGenreCount() const {
    return genre.size();
};

//not used but for when scores are added to films
double Movie::getAverageScore() const {
    if (this->reviewCount == 0) {
        return 0;
    }
    return ((double) this->reviewPoints) / (this->reviewCount);
};

//setters
void Movie::setTitle(string newTitle) {
    this->title = newTitle;
};

void Movie::setYear(unsigned int newYear) {
    this->year = newYear;
};

void Movie::setCert(MovieCertificate *newCert) {
    this->cert = newCert;
};

void Movie::setCert(string newCertName) {
    this->setCert(MovieDatabaseLink::getCert(newCertName, *(this->getParent())));

};

void Movie::setDuration(unsigned int newDuration) {
    this->duration = newDuration;
};

void Movie::setReviewAverage(double newReviewAverage) {
    this->reviewPoints = (unsigned int) newReviewAverage;
};


//add genre to  genre vector
void Movie::addGenre(MovieGenre *newGenre) {
    if (!hasGenre(newGenre)) {
        (this->genre).push_back(newGenre); //add genre to end of vector
    }
};

//checks the parent database if its a new genre and added if it is
void Movie::addGenre(string newGenreName) {
    this->addGenre(MovieDatabaseLink::getGenre(newGenreName, *(this->getParent())));
};

//checks for genre and cert
bool Movie::hasGenre(MovieGenre *findGenre) {
    int i = -1;
    int ii = genre.size();
    while (++i < ii) {
        if (genre[i] == findGenre) {
            return true;
        }
    }
    return false;
}

bool Movie::hasCert(MovieCertificate *findCert) {
    if (cert == findCert) {
        return true;
    }
    return false;
}







