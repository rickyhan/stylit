//
// Created by antoinewdg on 12/3/16.
//

#ifndef STYLIT_LOGGER_H
#define STYLIT_LOGGER_H

#include <boost/filesystem.hpp>
#include <fstream>
#include "utils.h"

namespace fs = boost::filesystem;

class Logger {
public:
    Logger(string style, string target, time_t t) : scale(0), n_iter(0) {
        root = _file_root() + "out/" + std::to_string(t) + "/" + target + "/" +
               style + "/";

        fs::create_directories(fs::path(root + "distances"));

        cout << "Processing style " << style << " for target " << target << endl;
    }

    inline string slug() {
        return std::to_string(scale) + '_' + std::to_string(n_iter);
    }

    void next_scale() {
        scale++;
        n_iter = 0;
    }

    void next_iter() {
        n_iter++;
    }

    void log_image(Mat_<Vec3b> image) {
        string filename = root + slug() + ".png";

        cv::imwrite(filename, image);
    }

    void log_distances(const vector<float> &distances, float a, float b) {
        write_to_file(root + "distances/" + slug() + ".txt", distances, a, b);
    }

    template<class T>
    static void write_to_file(string filename, const std::vector<T> &data, float a, float b) {
        std::ofstream out(filename);
        out << a << " " << b;
        for (const T &d : data) {
            out << " " << d;
        }
        out.close();
    }

private:
    string root;
    int scale;
    int n_iter;
};

#endif //STYLIT_LOGGER_H
