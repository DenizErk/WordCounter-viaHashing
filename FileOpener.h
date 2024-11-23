#pragma once

std::string sgmStringTransporter(int index) {
    std::string sgmFile = "reut2-000.sgm";
    if (index <= 9) {
        sgmFile[8] = index + 48;
    }
    else {
        sgmFile[7] = ((index - (index % 10)) / 10) + 48;
        sgmFile[8] = (index % 10) + 48;
    }
    return sgmFile;
}



