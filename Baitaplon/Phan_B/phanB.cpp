#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <cstring>

using namespace std;

// Lop Node de tao danh sach lien ket don
class Node {
public:
    int dinh;
    Node* keTiep;
    
    Node(int v) : dinh(v), keTiep(nullptr) {}
};

// Lop Graph
class DoThi {
private:
    int soDinh;
    vector<Node*> danhSachKe;  // Danh sach ke

    // Ham giup DFS duyet do thi
    void DFSUtil(int dinh, vector<bool>& daDuyet) {
        daDuyet[dinh] = true;
        cout << dinh << " ";
        for (Node* ke = danhSachKe[dinh]; ke != nullptr; ke = ke->keTiep) {
            if (!daDuyet[ke->dinh]) {
                DFSUtil(ke->dinh, daDuyet);
            }
        }
    }

public:
    DoThi(int soDinh) : soDinh(soDinh) {
        danhSachKe.resize(soDinh, nullptr);
    }

    // Doc do thi tu file
    void docDoThiTuFile(const string& tenFile) {
        ifstream file(tenFile);
        int u, v;
        while (file >> u >> v) {
            themCanh(u, v);
        }
        file.close();
    }

    // Ghi do thi ra file
    void ghiDoThiRaFile(const string& tenFile) {
        ofstream file(tenFile);
        for (int i = 0; i < soDinh; i++) {
            Node* tam = danhSachKe[i];
            while (tam) {
                file << i << " " << tam->dinh << endl;
                tam = tam->keTiep;
            }
        }
        file.close();
    }

    // Them canh vao do thi
    void themCanh(int u, int v) {
        Node* nodeV = new Node(v);
        nodeV->keTiep = danhSachKe[u];
        danhSachKe[u] = nodeV;
        
        // Vi do thi vo huong, ta can them canh nguoc lai
        Node* nodeU = new Node(u);
        nodeU->keTiep = danhSachKe[v];
        danhSachKe[v] = nodeU;
    }

    // Dem so thanh phan lien thong su dung DFS
    int demThanhPhanLienThong() {
        vector<bool> daDuyet(soDinh, false);
        int dem = 0;
        for (int i = 0; i < soDinh; i++) {
            if (!daDuyet[i]) {
                DFSUtil(i, daDuyet);
                cout << endl;
                dem++;
            }
        }
        return dem;
    }

    // Kiem tra co duong di giua 2 dinh su dung BFS
    bool coDuongDi(int batDau, int ketThuc) {
        if (batDau == ketThuc) return true;
        vector<bool> daDuyet(soDinh, false);
        queue<int> hangDoi;
        hangDoi.push(batDau);
        daDuyet[batDau] = true;
        
        while (!hangDoi.empty()) {
            int dinhHienTai = hangDoi.front();
            hangDoi.pop();
            
            for (Node* ke = danhSachKe[dinhHienTai]; ke != nullptr; ke = ke->keTiep) {
                if (!daDuyet[ke->dinh]) {
                    if (ke->dinh == ketThuc) {
                        return true;
                    }
                    daDuyet[ke->dinh] = true;
                    hangDoi.push(ke->dinh);
                }
            }
        }
        return false;
    }
};

int main() {
    int soDinh;
    cout << "Nhap so luong dinh cua do thi: ";
    cin >> soDinh;
    
    DoThi doThi(soDinh);

    // Doc do thi tu file
    string tenFileDauVao = "doThi.txt";
    doThi.docDoThiTuFile(tenFileDauVao);
    
    cout << "Do thi da doc tu file " << tenFileDauVao << ":\n";
    doThi.ghiDoThiRaFile("ghi_doThi.txt");
    
    // Dem so thanh phan lien thong trong do thi
    cout << "So thanh phan lien thong trong do thi la: " << doThi.demThanhPhanLienThong() << endl;

    // Kiem tra co duong di giua 2 dinh
    int u, v;
    cout << "Nhap 2 dinh de kiem tra duong di (u v): ";
    cin >> u >> v;
    if (doThi.coDuongDi(u, v)) {
        cout << "Co duong di tu " << u << " den " << v << endl;
    } else {
        cout << "Khong co duong di tu " << u << " den " << v << endl;
    }

    return 0;
}
