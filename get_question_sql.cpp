#include <iostream>
#include <fstream>
#include <string>
#include <sqlite3.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <vector>

class quiz {
public:
    std::string question;
};

std::vector<quiz> questions;

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    quiz q;

    for (int i = 0; i < argc; i++) {
        if (azColName[i] == "question") {
            q.question = argv[i] ? argv[i] : "NULL";
        }
    }

    questions.push_back(q);
    return 0;
}

int request(sqlite3 *db, std::string sql, char *zErrMsg) {
    const char *cstr = sql.c_str();
    int rc = sqlite3_exec(db, cstr, callback, 0, &zErrMsg);
   
    if( rc != SQLITE_OK ){
        std::cerr << "SQL error: " << zErrMsg << "." << std::endl;
        sqlite3_free(zErrMsg);
        return 0;
    } else {
        return SQLITE_OK;
    }

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <sqlite_db>" << std::endl;
        return 0;
    }

    const char* filename_db = argv[1];
    sqlite3* db = nullptr;
    char* zErrMsg;

    int rc = sqlite3_open(filename_db, &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return rc;
    }

    request(db, "select * from quiz;", zErrMsg);

    for (quiz item : questions) {
        std::string question = item.question;

        std::cout << "Question:" << std::endl;
        std::cout << question << std::endl;
        std::cout << std::endl;
    }

    sqlite3_close(db);

    free(zErrMsg);
    free(db);

    return 0;
}
