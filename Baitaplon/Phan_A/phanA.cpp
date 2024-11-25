#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <fstream>

using namespace std;

class SinhVien {
private:
    string tenSV;
    string lop;
    string maSV;
    double diem;

public:
    SinhVien(string ten = "", string lop = "", string maSV = "", double diem = 0.0)
        : tenSV(ten), lop(lop), maSV(maSV), diem(diem) {}

    string getTenSV() const { return tenSV; }
    string getLop() const { return lop; }
    string getMaSV() const { return maSV; }
    double getDiem() const { return diem; }

    void setTenSV(const string& ten) { tenSV = ten; }
    void setLop(const string& l) { lop = l; }
    void setMaSV(const string& ma) { maSV = ma; }
    void setDiem(double d) { diem = d; }

    void inSV() const {
        cout << "MSSV: " << maSV << ", Ten: " << tenSV << ", Lop: " << lop << ", Diem: " << diem << endl;
    }

    void inSVXepLoai() const {
        string xepLoai = (diem >= 8.0) ? "Gioi" : (diem >= 6.5) ? "Kha" : (diem >= 5.0) ? "Trung Binh" : "Yeu";
        cout << tenSV << " - Xep loai: " << xepLoai << endl;
    }

    bool operator<(const SinhVien& other) const {
        return diem > other.diem; // So sánh di?m d? s?p x?p theo th? t? gi?m d?n
    }
};

class DanhSachSV {
private:
    list<SinhVien> ds;

public:
    void nhapDS() {
        int n;
        cout << "Nhap so sinh vien: ";
        cin >> n;
        for (int i = 0; i < n; i++) {
            string ten, lop, maSV;
            double diem;
            cout << "Nhap thong tin sinh vien thu " << i + 1 << ":\n";
            cout << "Ten: "; cin.ignore(); getline(cin, ten);
            cout << "Lop: "; getline(cin, lop);
            cout << "MSSV: "; getline(cin, maSV);
            cout << "Diem: "; cin >> diem;
            SinhVien sv(ten, lop, maSV, diem);
            ds.push_back(sv);
        }
    }

    void inDS() const {
        for (const auto& sv : ds) {
            sv.inSV();
        }
    }

    void inDSXepLoai() const {
        for (const auto& sv : ds) {
            sv.inSVXepLoai();
        }
    }

    void timSVTheoTenLop(const string& ten, const string& lop) const {
        bool found = false;
        for (const auto& sv : ds) {
            if (sv.getTenSV() == ten && sv.getLop() == lop) {
                cout << "MSSV: " << sv.getMaSV() << endl;
                found = true;
            }
        }
        if (!found) cout << "Khong tim thay sinh vien.\n";
    }

    void themSV(const SinhVien& sv) {
        ds.push_back(sv);
    }

    void xoaSVTheoLop(const string& lop) {
        ds.remove_if([&lop](const SinhVien& sv) { return sv.getLop() == lop; });
    }

    void sapXepDS() {
        ds.sort();
    }

    void chenSV(const SinhVien& sv) {
        ds.push_back(sv);
        sapXepDS();
    }

    void luuDSVaoFile(const string& filename) {
        ofstream outFile(filename);
        for (const auto& sv : ds) {
            outFile << sv.getMaSV() << "," << sv.getTenSV() << "," << sv.getLop() << "," << sv.getDiem() << endl;
        }
        outFile.close();
        cout << "Danh sach sinh vien da duoc luu vao file.\n";
    }
};

class App {
private:
    DanhSachSV ds;

public:
    void hienMenu() {
        cout << "---- MENU ----\n";
        cout << "1. Nhap danh sach sinh vien\n";
        cout << "2. In danh sach sinh vien\n";
        cout << "3. In danh sach sinh vien voi xep loai\n";
        cout << "4. Tim sinh vien theo ten va lop\n";
        cout << "5. Them sinh vien\n";
        cout << "6. Xoa sinh vien theo lop\n";
        cout << "7. Sap xep danh sach\n";
        cout << "8. Chen sinh vien ma khong doi\n";
        cout << "9. Luu danh sach vao file\n";
        cout << "10. Thoat\n";
        cout << "Chon thao tac: ";
    }

    void xuLy() {
        int chon;
        while (true) {
            hienMenu();
            cin >> chon;
            cin.ignore();  // Ð? b? qua ký t? '\n' trong b? d?m

            switch (chon) {
                case 1:
                    ds.nhapDS();
                    break;
                case 2:
                    ds.inDS();
                    break;
                case 3:
                    ds.inDSXepLoai();
                    break;
                case 4: {
                    string ten, lop;
                    cout << "Nhap ten sinh vien: "; getline(cin, ten);
                    cout << "Nhap lop: "; getline(cin, lop);
                    ds.timSVTheoTenLop(ten, lop);
                    break;
                }
                case 5: {
                    string ten, lop, maSV;
                    double diem;
                    cout << "Nhap ten sinh vien: "; getline(cin, ten);
                    cout << "Nhap lop: "; getline(cin, lop);
                    cout << "Nhap ma sinh vien: "; getline(cin, maSV);
                    cout << "Nhap diem: "; cin >> diem;
                    SinhVien sv(ten, lop, maSV, diem);
                    ds.themSV(sv);
                    break;
                }
                case 6: {
                    string lop;
                    cout << "Nhap lop can xoa sinh vien: "; getline(cin, lop);
                    ds.xoaSVTheoLop(lop);
                    break;
                }
                case 7:
                    ds.sapXepDS();
                    break;
                case 8: {
                    string ten, lop, maSV;
                    double diem;
                    cout << "Nhap ten sinh vien: "; getline(cin, ten);
                    cout << "Nhap lop: "; getline(cin, lop);
                    cout << "Nhap ma sinh vien: "; getline(cin, maSV);
                    cout << "Nhap diem: "; cin >> diem;
                    SinhVien sv(ten, lop, maSV, diem);
                    ds.chenSV(sv);
                    break;
                }
                case 9: {
                    string filename;
                    cout << "Nhap ten file luu danh sach: "; getline(cin, filename);
                    ds.luuDSVaoFile(filename);
                    break;
                }
                case 10:
                    cout << "Thoat chuong trinh.\n";
                    return;
                default:
                    cout << "Lua chon khong hop le.\n";
            }
        }
    }
};

int main() {
    App app;
    app.xuLy();
    return 0;
}

