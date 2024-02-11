#include "ppm_image.h"

#include <array>
#include <fstream>
#include <string_view>

using namespace std;

namespace img_lib {

    static const string_view PPM_SIG = "P6"sv;
    static const int PPM_MAX = 255;

    // ���������� ��� ������� ��������������
    bool SavePPM(const Path& file, const Image& image) {
        int w = image.GetWidth();
        int h = image.GetHeight();

        ofstream ofs(file, ios::binary);
        if (!ofs) return false;
        
        ofs << PPM_SIG 
            << w << ' ' 
            << h << '\n'
            << PPM_MAX << '\n';

        std::vector<char> buff(w * 3);

        for (int i = 0; i < h; ++i) {
            const Color* line = image.GetLine(i);
            for (int j = 0; j < w; j++) {
                buff[j*3] = static_cast<char>(line[j].r);
                buff[j*3 + 1] = static_cast<char>(line[j].g);
                buff[j*3 + 2] = static_cast<char>(line[j].b);
            }
            ofs.write(buff.data(), buff.size());
            if (!ofs) return false;
        }
        
        return true;
    }

    Image LoadPPM(const Path& file) {
        // ��������� ����� � ������ ios::binary
        // ��������� ����� ������ ����� � �������� �������
        ifstream ifs(file, ios::binary);
        std::string sign;
        int w, h, color_max;

        // ������ ���������: �� �������� ������, ������� �����������
        // � ������������ �������� �����
        ifs >> sign >> w >> h >> color_max;

        // �� ������������ ����������� ������ ������� P6
        // � ������������ ��������� ����� 255
        if (sign != PPM_SIG || color_max != PPM_MAX) {
            return {};
        }

        // ���������� ���� ���� - ��� ����� ������
        const char next = ifs.get();
        if (next != '\n') {
            return {};
        }

        Image result(w, h, Color::Black());
        std::vector<char> buff(w * 3);

        for (int y = 0; y < h; ++y) {
            Color* line = result.GetLine(y);
            ifs.read(buff.data(), w * 3);

            for (int x = 0; x < w; ++x) {
                line[x].r = static_cast<byte>(buff[x * 3 + 0]);
                line[x].g = static_cast<byte>(buff[x * 3 + 1]);
                line[x].b = static_cast<byte>(buff[x * 3 + 2]);
            }
        }

        return result;
    }

    void NegateInplace(img_lib::Image& image) {
        for (int i = 0; i < image.GetHeight(); ++i) {
            Color* line = image.GetLine(i);
            for (int j = 0; j < image.GetWidth(); ++j) {
                line[j].r = ~line[j].r;
                line[j].g = ~line[j].g;
                line[j].b = ~line[j].b;
            }
        }

    }

}  // namespace img_lib
