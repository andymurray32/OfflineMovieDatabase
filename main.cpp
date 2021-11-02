
// author: 100214063

#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

#include "MovieDatabase.h"



string wordFile = "films.txt";

int main(int argc, char **argv) {

    MovieDatabase *myDB = new MovieDatabase();

    cout << wordFile << " file added to database\n";
    ifstream movieCSV(wordFile);
    movieCSV >> *myDB;

    cout << "\nTask 1:\n";
    cout << "Sort the movies in ascending order of release date and display on console:\n\n";

    myDB->sortDatabase(MovieDatabase::SortFields::year, false);
    cout << "Movie list:\n\n";
    cout << *myDB;


    cout << "\n\nTask 2:\n";
    cout << "Display the third longest Film-Noir:\n\n";

    MovieGenre *filmNoirGenre = myDB->getGenre("Film-Noir");
    MovieDatabase *filmNoirFilms = myDB->genreList(filmNoirGenre);
    filmNoirFilms->sortDatabase(MovieDatabase::SortFields::duration, true);
    int posCheck = 3;
    if (filmNoirFilms->count() < posCheck) {
        cout << "Not enough films!";
    } else {
        cout << (*(filmNoirFilms->getIndex(posCheck - 1)));
        //cout << *filmNoirFilms;
    }

    cout << "\n\nTask 3:\n";
    cout << "Display the eighth most recent UNRATED movie:\n\n";
    MovieCertificate *filmCert = myDB->getCert("UNRATED");
    MovieDatabase *unratedFilm = myDB->certList(filmCert);
    unratedFilm->sortDatabase(MovieDatabase::SortFields::year, true);
    int psCheck = 8;
    if (unratedFilm->count() < psCheck) {
        cout << "Not enough films!";
    } else {
        cout << (*(unratedFilm->getIndex(psCheck - 1)));
        //cout << *unratedFilm;
    }

    cout << "\n\nTask 4:\n";
    cout << "Display the movie with the longest title:\n\n";

    myDB->sortDatabase(MovieDatabase::title_length, true);
    int psCheck2 = 1;
    if (myDB->count() < psCheck2) {
        cout << "Not enough films!";
    } else {
        cout << (*(myDB->getIndex(psCheck2 - 1)));
        //cout << *myDB;
    }


    return EXIT_SUCCESS;
}

