#include <iostream>           // Thư viện nhập/xuất chuẩn
#include <fstream>            // Thư viện thao tác với file
#include <sstream>            // Thư viện xử lý luồng chuỗi
#include <string>             // Thư viện xử lý chuỗi
#include <vector>             // Thư viện vector
#include <iomanip>            // Thư viện định dạng đầu ra
#include <ctime>              // Thư viện xử lý thời gian
#include <cstdlib>            // Thư viện hàm chuẩn (rand, srand,...)
#include <windows.h>          // Thư viện cho các hàm Windows (Sleep, SetConsoleOutputCP,...)
#include <direct.h>           // Thư viện tạo thư mục (_mkdir)
#include <sys/stat.h>         // Thư viện kiểm tra thông tin file/thư mục (stat)
#include <locale>             // Thư viện locale cho xử lý ngôn ngữ
using namespace std;          // Sử dụng không gian tên chuẩn

//--------------------- Utility Functions ---------------------

// Kiểm tra sự tồn tại của thư mục
bool directoryExists(const string &path) {       // Hàm kiểm tra thư mục tồn tại hay không
    struct stat info;                            // Tạo biến struct stat để lưu thông tin
    if (stat(path.c_str(), &info) != 0)             // Nếu không truy cập được thư mục
        return false;                            // Trả về false
    else if (info.st_mode & S_IFDIR)               // Nếu thuộc tính cho biết đây là thư mục
        return true;                             // Trả về true
    else                                         
        return false;                            // Ngược lại trả về false
}

// Tạo thư mục nếu chưa tồn tại
void createDirectoryIfNotExists(const string &path) { // Hàm tạo thư mục nếu chưa tồn tại
    if (!directoryExists(path)) {                // Nếu thư mục không tồn tại
        if (_mkdir(path.c_str()) == 0) {          // Thử tạo thư mục, nếu thành công (_mkdir trả về 0)
            cout << "Đã tạo thư mục: " << path << endl;  // Thông báo tạo thư mục thành công
        } else {                                
            cout << "Lỗi khi tạo thư mục: " << path << endl; // Thông báo lỗi tạo thư mục
        }
    }
}

// Kiểm tra file có tồn tại hay không
bool fileExists(const string &fileName) {        // Hàm kiểm tra sự tồn tại của file
    ifstream file(fileName);                     // Mở file dưới dạng ifstream
    return file.good();                          // Nếu file mở thành công thì good() trả về true
}

// Lấy chuỗi ngày hiện tại theo định dạng "dd_mm_yyyy"
string getCurrentDate() {                        // Hàm lấy ngày hiện tại
    time_t now = time(0);                        // Lấy thời gian hiện tại
    tm *ltm = localtime(&now);                   // Chuyển đổi thời gian sang cấu trúc tm
    ostringstream oss;                           // Tạo luồng xuất chuỗi để xây dựng chuỗi ngày
    oss << ltm->tm_mday << "_" << (1 + ltm->tm_mon) << "_" << (1900 + ltm->tm_year); // Định dạng thành "dd_mm_yyyy"
    return oss.str();                            // Trả về chuỗi ngày
}

// Tạo mã ngẫu nhiên với độ dài mặc định là 15 ký tự
string generateRandomCode(int length = 15) {     // Hàm tạo mã ngẫu nhiên với độ dài mặc định 15
    const string characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // Chuỗi chứa các ký tự cho mã
    string result;                               // Biến lưu kết quả
    for (int i = 0; i < length; i++) {           // Lặp từ 0 đến length-1
        result.push_back(characters[rand() % characters.size()]); // Lấy ký tự ngẫu nhiên từ chuỗi characters
    }
    return result;                               // Trả về chuỗi mã ngẫu nhiên
}

// Xoá màn hình console
void clearScreen() {                             // Hàm xoá màn hình console
    system("CLS");                               // Gọi lệnh hệ thống để xoá màn hình (trên Windows)
}

// Hiển thị thông báo chờ với khoảng thời gian cho trước
void showWaitMessage(const string &message, int seconds = 3) { // Hàm hiển thị thông báo chờ
    cout << message;                           // In thông báo ra màn hình
    for (int i = 0; i < seconds; i++) {          // Lặp theo số giây chờ
        Sleep(1000);                           // Dừng 1 giây (1000 mili giây)
        cout << ".";                           // In dấu chấm
    }
    cout << endl;                              // Xuống dòng sau khi hoàn thành
}

//--------------------- Lớp Employee ---------------------

class Employee {                               // Định nghĩa lớp Employee
public:
    string id;                                 // Thuộc tính mã nhân viên
    string name;                               // Thuộc tính tên nhân viên
    string birthDate;                          // Thuộc tính ngày sinh
    string workHours;                          // Thuộc tính giờ làm
    string area;                               // Thuộc tính khu vực

    // Chuyển thông tin nhân viên thành chuỗi để hiển thị
    string display() const {                     // Hàm chuyển thông tin nhân viên thành chuỗi hiển thị
        ostringstream oss;                     // Tạo luồng xuất chuỗi
        oss << "Mã: " << id                   // Ghi mã nhân viên
            << " | Tên: " << name             // Ghi tên nhân viên
            << " | Ngày Sinh: " << birthDate   // Ghi ngày sinh
            << " | Giờ Làm: " << workHours      // Ghi giờ làm
            << " | Khu Vực: " << area;         // Ghi khu vực
        return oss.str();                      // Trả về chuỗi kết quả
    }

    // Chuyển đổi thông tin thành chuỗi lưu file (sử dụng dấu '|' làm phân cách)
    string toFileString() const {                // Hàm chuyển thông tin thành chuỗi lưu file
        ostringstream oss;                      // Tạo luồng xuất chuỗi
        oss << id << "|" << name << "|" << birthDate << "|" << workHours << "|" << area; // Ghép thông tin với dấu phân cách '|'
        return oss.str();                       // Trả về chuỗi kết quả
    }

    // Tạo đối tượng Employee từ chuỗi đọc từ file
    static Employee fromFile(const string &line) { // Hàm tạo đối tượng Employee từ chuỗi
        Employee emp;                          // Tạo đối tượng Employee
        istringstream iss(line);               // Tạo luồng nhập chuỗi từ dòng đã đọc
        getline(iss, emp.id, '|');             // Đọc mã nhân viên từ chuỗi, phân cách bởi '|'
        getline(iss, emp.name, '|');           // Đọc tên nhân viên
        getline(iss, emp.birthDate, '|');      // Đọc ngày sinh
        getline(iss, emp.workHours, '|');      // Đọc giờ làm
        getline(iss, emp.area, '|');           // Đọc khu vực
        return emp;                            // Trả về đối tượng Employee
    }
};

//--------------------- Lớp Customer ---------------------

class Customer {                               // Định nghĩa lớp Customer
public:
    string id;                                 // Thuộc tính mã khách hàng
    string name;                               // Thuộc tính tên khách hàng
    string purchaseDate;                       // Thuộc tính ngày mua
    string product;                            // Thuộc tính sản phẩm
    string quantity;                           // Thuộc tính số lượng
    double totalAmount;                        // Thuộc tính tổng tiền
    double discount;                           // Thuộc tính giảm giá

    // Hiển thị thông tin khách hàng
    string display() const {                     // Hàm hiển thị thông tin khách hàng
        ostringstream oss;                     // Tạo luồng xuất chuỗi
        oss << "Mã: " << id                   // Ghi mã khách hàng
            << " | Tên: " << name             // Ghi tên khách hàng
            << " | Ngày Mua: " << purchaseDate // Ghi ngày mua
            << " | Sản Phẩm: " << product      // Ghi sản phẩm
            << " | Số Lượng: " << quantity      // Ghi số lượng
            << " | Tổng Tiền: " << totalAmount  // Ghi tổng tiền
            << " | Giảm Giá: " << discount      // Ghi giảm giá
            << " | Thanh Toán: " << (totalAmount - discount); // Tính tiền thanh toán (tổng tiền - giảm giá)
        return oss.str();                      // Trả về chuỗi kết quả
    }

    // Chuyển đổi thông tin thành chuỗi lưu file
    string toFileString() const {                // Hàm chuyển đổi thông tin khách hàng thành chuỗi lưu file
        ostringstream oss;                      // Tạo luồng xuất chuỗi
        oss << id << "|" << name << "|" << purchaseDate << "|" << product 
            << "|" << quantity << "|" << totalAmount << "|" << discount; // Ghép thông tin với dấu phân cách '|'
        return oss.str();                       // Trả về chuỗi kết quả
    }

    // Tạo đối tượng Customer từ chuỗi đọc từ file
    static Customer fromFile(const string &line) { // Hàm tạo đối tượng Customer từ chuỗi file
        Customer cust;                         // Tạo đối tượng Customer
        istringstream iss(line);               // Tạo luồng nhập chuỗi từ dòng đã đọc
        string token;                          // Biến tạm lưu giá trị chuỗi cho các số
        getline(iss, cust.id, '|');            // Đọc mã khách hàng
        getline(iss, cust.name, '|');          // Đọc tên khách hàng
        getline(iss, cust.purchaseDate, '|');  // Đọc ngày mua
        getline(iss, cust.product, '|');       // Đọc sản phẩm
        getline(iss, cust.quantity, '|');      // Đọc số lượng
        getline(iss, token, '|');              // Đọc tổng tiền dưới dạng chuỗi
        cust.totalAmount = stod(token);        // Chuyển chuỗi thành số thực và gán vào totalAmount
        getline(iss, token, '|');              // Đọc giảm giá dưới dạng chuỗi
        cust.discount = stod(token);           // Chuyển chuỗi thành số thực và gán vào discount
        return cust;                           // Trả về đối tượng Customer
    }
};

//--------------------- Lớp ManagementSystem ---------------------
// Quản lý dữ liệu của Employee và Customer theo ngày
class ManagementSystem {                         // Định nghĩa lớp quản lý hệ thống dữ liệu
private:
    string currentDate;                        // Ngày được chọn (định dạng dd_mm_yyyy)
    string employeeFile;                       // Tên file lưu dữ liệu nhân viên
    string customerFile;                       // Tên file lưu dữ liệu khách hàng
    // Các file thống kê có thể được tính lại từ customerFile

    // Cập nhật tên file dựa trên ngày (vd: data/staff_dd_mm_yyyy.txt)
    void updateFileNames(const string &date) {  // Hàm cập nhật tên file dựa trên ngày
        currentDate = date;                    // Gán ngày được chọn
        employeeFile = "data/staff_" + currentDate + ".txt";  // Tạo tên file cho nhân viên
        customerFile = "data/client_" + currentDate + ".txt";   // Tạo tên file cho khách hàng
    }

public:
    ManagementSystem() {                       // Hàm khởi tạo của ManagementSystem
        // Mặc định sử dụng ngày hiện tại
        updateFileNames(getCurrentDate());     // Cập nhật tên file với ngày hiện tại
    }

    // Đổi ngày quản lý (dùng để xem dữ liệu cũ)
    void changeDate(const string &date) {      // Hàm thay đổi ngày quản lý dữ liệu
        updateFileNames(date);                 // Cập nhật tên file dựa trên ngày mới
    }

    //--------------------- Quản lý Employee ---------------------

    // Thêm Employee (Create)
    void addEmployee(int count) {              // Hàm thêm nhân viên với số lượng được chỉ định
        ofstream fout(employeeFile, ios::app); // Mở file nhân viên với chế độ ghi thêm (append)
        if (!fout) {                           // Nếu mở file không thành công
            cout << "Lỗi mở file: " << employeeFile << endl; // Hiển thị thông báo lỗi
            return;                            // Kết thúc hàm
        }
        for (int i = 0; i < count; i++) {        // Lặp theo số lượng nhân viên cần thêm
            Employee emp;                      // Tạo đối tượng Employee mới
            cout << "\nNhân Viên thứ " << i + 1 << endl; // Hiển thị số thứ tự của nhân viên
            cout << "(Nhập tiếng việt không dấu)" << endl;
            cout << "Nhập Tên: ";              // Yêu cầu nhập tên
            getline(cin, emp.name);            // Đọc tên từ bàn phím
            cout << "Nhập Ngày Sinh: ";        // Yêu cầu nhập ngày sinh
            getline(cin, emp.birthDate);       // Đọc ngày sinh từ bàn phím
            cout << "Nhập Giờ Làm: ";           // Yêu cầu nhập giờ làm
            getline(cin, emp.workHours);       // Đọc giờ làm từ bàn phím
            cout << "Nhập Khu Vực: ";          // Yêu cầu nhập khu vực
            getline(cin, emp.area);            // Đọc khu vực từ bàn phím
            emp.id = "EMP_" + generateRandomCode(); // Tạo mã nhân viên ngẫu nhiên với tiền tố "EMP_"
            fout << emp.toFileString() << endl;  // Ghi thông tin nhân viên vào file
        }
        fout.close();                          // Đóng file sau khi ghi xong
        cout << "\nĐã thêm " << count << " nhân viên thành công!" << endl; // Thông báo thành công
    }

    // Xem danh sách Employee (Read)
    void viewEmployees() {                     // Hàm xem danh sách nhân viên
        ifstream fin(employeeFile);            // Mở file nhân viên để đọc
        if (!fin) {                            // Nếu file không mở được
            cout << "Không có dữ liệu nhân viên cho ngày: " << currentDate << endl; // Thông báo lỗi
            return;                            // Kết thúc hàm
        }
        string line;                           // Biến lưu từng dòng dữ liệu
        vector<Employee> employees;            // Tạo vector để lưu danh sách nhân viên
        while (getline(fin, line)) {           // Đọc từng dòng trong file
            if (line.empty()) continue;        // Nếu dòng trống, bỏ qua
            employees.push_back(Employee::fromFile(line)); // Chuyển đổi dòng dữ liệu thành đối tượng Employee và thêm vào vector
        }
        fin.close();                           // Đóng file đọc
        cout << "\nTổng số Nhân Viên: " << employees.size() << endl; // Hiển thị tổng số nhân viên
        for (const auto &emp : employees) {    // Duyệt qua từng nhân viên
            cout << emp.display() << endl;     // In ra thông tin nhân viên
        }
    }

    // Cập nhật Employee (Update)
    void updateEmployee() {                    // Hàm cập nhật thông tin nhân viên
        ifstream fin(employeeFile);            // Mở file nhân viên để đọc
        if (!fin) {                            // Nếu mở file không thành công
            cout << "Không có dữ liệu nhân viên cho ngày: " << currentDate << endl; // Thông báo lỗi
            return;                            // Kết thúc hàm
        }
        vector<Employee> employees;            // Tạo vector lưu danh sách nhân viên
        string line;                           // Biến lưu từng dòng dữ liệu
        while (getline(fin, line)) {           // Đọc từng dòng trong file
            if (line.empty()) continue;        // Nếu dòng trống, bỏ qua
            employees.push_back(Employee::fromFile(line)); // Chuyển dòng dữ liệu thành đối tượng Employee và thêm vào vector
        }
        fin.close();                           // Đóng file đọc

        cout << "Nhập mã nhân viên cần cập nhật: "; // Yêu cầu nhập mã nhân viên cần cập nhật
        string id;                           // Biến lưu mã nhân viên
        getline(cin, id);                    // Đọc mã nhân viên từ bàn phím
        bool found = false;                  // Biến đánh dấu đã tìm thấy nhân viên hay chưa
        for (auto &emp : employees) {        // Duyệt qua từng nhân viên
            if (emp.id == id) {              // Nếu mã nhân viên khớp
                found = true;                // Đánh dấu đã tìm thấy
                cout << "Cập nhật thông tin cho nhân viên có mã " << id << endl; // Thông báo cập nhật nhân viên có mã đó
                cout << "Nhập Tên mới (Enter nếu không thay đổi): "; // Yêu cầu nhập tên mới
                string newName;              // Biến lưu tên mới
                getline(cin, newName);       // Đọc tên mới từ bàn phím
                if (!newName.empty()) emp.name = newName; // Nếu có nhập thì cập nhật tên
                cout << "Nhập Ngày Sinh mới (Enter nếu không thay đổi): "; // Yêu cầu nhập ngày sinh mới
                string newBirthDate;         // Biến lưu ngày sinh mới
                getline(cin, newBirthDate);  // Đọc ngày sinh mới
                if (!newBirthDate.empty()) emp.birthDate = newBirthDate; // Nếu có nhập thì cập nhật ngày sinh
                cout << "Nhập Giờ Làm mới (Enter nếu không thay đổi): "; // Yêu cầu nhập giờ làm mới
                string newWorkHours;         // Biến lưu giờ làm mới
                getline(cin, newWorkHours);  // Đọc giờ làm mới
                if (!newWorkHours.empty()) emp.workHours = newWorkHours; // Nếu có nhập thì cập nhật giờ làm
                cout << "Nhập Khu Vực mới (Enter nếu không thay đổi): "; // Yêu cầu nhập khu vực mới
                string newArea;              // Biến lưu khu vực mới
                getline(cin, newArea);       // Đọc khu vực mới
                if (!newArea.empty()) emp.area = newArea; // Nếu có nhập thì cập nhật khu vực
                break;                       // Thoát vòng lặp sau khi cập nhật
            }
        }
        if (!found) {                        // Nếu không tìm thấy nhân viên cần cập nhật
            cout << "Không tìm thấy nhân viên có mã " << id << endl; // Hiển thị thông báo lỗi
            return;                        // Kết thúc hàm
        }
        // Ghi lại dữ liệu đã cập nhật
        ofstream fout(employeeFile, ios::trunc); // Mở file nhân viên với chế độ ghi đè (trunc)
        for (auto &emp : employees) {        // Duyệt qua từng nhân viên
            fout << emp.toFileString() << endl; // Ghi thông tin nhân viên vào file
        }
        fout.close();                        // Đóng file
        cout << "Cập nhật nhân viên thành công!" << endl; // Thông báo cập nhật thành công
    }

    // Xóa Employee (Delete)
    void deleteEmployee() {                    // Hàm xóa nhân viên
        ifstream fin(employeeFile);            // Mở file nhân viên để đọc
        if (!fin) {                            // Nếu không mở được file
            cout << "Không có dữ liệu nhân viên cho ngày: " << currentDate << endl; // Hiển thị thông báo lỗi
            return;                            // Kết thúc hàm
        }
        vector<Employee> employees;            // Tạo vector lưu danh sách nhân viên
        string line;                           // Biến lưu từng dòng dữ liệu
        while (getline(fin, line)) {           // Đọc từng dòng trong file
            if (line.empty()) continue;        // Nếu dòng trống, bỏ qua
            employees.push_back(Employee::fromFile(line)); // Chuyển đổi dòng dữ liệu thành đối tượng Employee và thêm vào vector
        }
        fin.close();                           // Đóng file đọc

        cout << "Nhập mã nhân viên cần xóa: "; // Yêu cầu nhập mã nhân viên cần xóa
        string id;                           // Biến lưu mã nhân viên
        getline(cin, id);                    // Đọc mã nhân viên từ bàn phím
        bool found = false;                  // Biến đánh dấu đã tìm thấy nhân viên cần xóa hay chưa
        vector<Employee> newEmployees;         // Tạo vector lưu danh sách nhân viên sau khi xóa
        for (auto &emp : employees) {        // Duyệt qua từng nhân viên
            if (emp.id == id) {              // Nếu mã nhân viên khớp
                found = true;                // Đánh dấu đã tìm thấy
                continue;                    // Bỏ qua nhân viên này (xóa)
            }
            newEmployees.push_back(emp);     // Thêm các nhân viên không xóa vào vector mới
        }
        if (!found) {                        // Nếu không tìm thấy nhân viên cần xóa
            cout << "Không tìm thấy nhân viên có mã " << id << endl; // Thông báo lỗi
            return;                        // Kết thúc hàm
        }
        // Ghi lại dữ liệu sau khi xóa
        ofstream fout(employeeFile, ios::trunc); // Mở file với chế độ ghi đè
        for (auto &emp : newEmployees) {      // Duyệt qua danh sách nhân viên còn lại
            fout << emp.toFileString() << endl; // Ghi thông tin nhân viên vào file
        }
        fout.close();                        // Đóng file
        cout << "Xóa nhân viên thành công!" << endl; // Thông báo xóa thành công
    }

    //--------------------- Quản lý Customer ---------------------

    // Thêm Customer (Create)
    void addCustomer(int count) {              // Hàm thêm khách hàng với số lượng được chỉ định
        ofstream fout(customerFile, ios::app); // Mở file khách hàng với chế độ ghi thêm (append)
        if (!fout) {                           // Nếu mở file không thành công
            cout << "Lỗi mở file: " << customerFile << endl; // Thông báo lỗi mở file
            return;                            // Kết thúc hàm
        }
        for (int i = 0; i < count; i++) {        // Lặp theo số lượng khách hàng cần thêm
            Customer cust;                     // Tạo đối tượng Customer mới
            cout << "\nKhách Hàng thứ " << i + 1 << endl; // Hiển thị số thứ tự khách hàng
            cout << "(Nhập tiếng việt không dấu)" << endl;
            cout << "Nhập Tên: ";              // Yêu cầu nhập tên khách hàng
            getline(cin, cust.name);           // Đọc tên khách hàng từ bàn phím
            cout << "Nhập Ngày Mua: ";         // Yêu cầu nhập ngày mua
            getline(cin, cust.purchaseDate);   // Đọc ngày mua từ bàn phím
            cout << "Nhập Tên Sản Phẩm: ";     // Yêu cầu nhập tên sản phẩm
            getline(cin, cust.product);        // Đọc tên sản phẩm từ bàn phím
            cout << "Nhập Số Lượng: ";         // Yêu cầu nhập số lượng
            getline(cin, cust.quantity);       // Đọc số lượng từ bàn phím
            cout << "Nhập Tổng Tiền: ";        // Yêu cầu nhập tổng tiền
            cin >> cust.totalAmount;           // Đọc tổng tiền từ bàn phím
            cout << "Nhập Giảm Giá: ";         // Yêu cầu nhập giảm giá
            cin >> cust.discount;              // Đọc giảm giá từ bàn phím
            cin.ignore();                      // Bỏ qua ký tự newline còn lại
            cust.id = "CUS_" + generateRandomCode(); // Tạo mã khách hàng ngẫu nhiên với tiền tố "CUS_"
            fout << cust.toFileString() << endl; // Ghi thông tin khách hàng vào file
        }
        fout.close();                        // Đóng file
        cout << "\nĐã thêm " << count << " khách hàng thành công!" << endl; // Thông báo thành công
    }

    // Xem danh sách Customer (Read)
    void viewCustomers() {                     // Hàm xem danh sách khách hàng
        ifstream fin(customerFile);            // Mở file khách hàng để đọc
        if (!fin) {                            // Nếu mở file không thành công
            cout << "Không có dữ liệu khách hàng cho ngày: " << currentDate << endl; // Thông báo lỗi
            return;                            // Kết thúc hàm
        }
        string line;                           // Biến lưu từng dòng dữ liệu
        vector<Customer> customers;            // Tạo vector lưu danh sách khách hàng
        while (getline(fin, line)) {           // Đọc từng dòng trong file
            if (line.empty()) continue;        // Nếu dòng trống, bỏ qua
            customers.push_back(Customer::fromFile(line)); // Chuyển đổi dòng dữ liệu thành đối tượng Customer và thêm vào vector
        }
        fin.close();                           // Đóng file đọc
        cout << "\nTổng số Khách Hàng: " << customers.size() << endl; // Hiển thị tổng số khách hàng
        for (const auto &cust : customers) {   // Duyệt qua từng khách hàng
            cout << cust.display() << endl;    // In ra thông tin khách hàng
        }
    }

    // Cập nhật Customer (Update)
    void updateCustomer() {                    // Hàm cập nhật thông tin khách hàng
        ifstream fin(customerFile);            // Mở file khách hàng để đọc
        if (!fin) {                            // Nếu mở file không thành công
            cout << "Không có dữ liệu khách hàng cho ngày: " << currentDate << endl; // Thông báo lỗi
            return;                            // Kết thúc hàm
        }
        vector<Customer> customers;            // Tạo vector lưu danh sách khách hàng
        string line;                           // Biến lưu từng dòng dữ liệu
        while (getline(fin, line)) {           // Đọc từng dòng trong file
            if (line.empty()) continue;        // Nếu dòng trống, bỏ qua
            customers.push_back(Customer::fromFile(line)); // Chuyển đổi dòng dữ liệu thành đối tượng Customer và thêm vào vector
        }
        fin.close();                           // Đóng file đọc

        cout << "Nhập mã khách hàng cần cập nhật: "; // Yêu cầu nhập mã khách hàng cần cập nhật
        string id;                           // Biến lưu mã khách hàng
        getline(cin, id);                    // Đọc mã khách hàng từ bàn phím
        bool found = false;                  // Biến đánh dấu đã tìm thấy khách hàng cần cập nhật
        for (auto &cust : customers) {         // Duyệt qua từng khách hàng
            if (cust.id == id) {             // Nếu mã khách hàng khớp
                found = true;                // Đánh dấu đã tìm thấy
                cout << "Cập nhật thông tin cho khách hàng có mã " << id << endl; // Thông báo cập nhật khách hàng có mã đó
                cout << "Nhập Tên mới (Enter nếu không thay đổi): "; // Yêu cầu nhập tên mới
                string newName;            // Biến lưu tên mới
                getline(cin, newName);     // Đọc tên mới từ bàn phím
                if (!newName.empty()) cust.name = newName; // Nếu có nhập, cập nhật tên
                cout << "Nhập Ngày Mua mới (Enter nếu không thay đổi): "; // Yêu cầu nhập ngày mua mới
                string newPurchaseDate;    // Biến lưu ngày mua mới
                getline(cin, newPurchaseDate); // Đọc ngày mua mới
                if (!newPurchaseDate.empty()) cust.purchaseDate = newPurchaseDate; // Nếu có nhập, cập nhật ngày mua
                cout << "Nhập Sản Phẩm mới (Enter nếu không thay đổi): "; // Yêu cầu nhập sản phẩm mới
                string newProduct;         // Biến lưu sản phẩm mới
                getline(cin, newProduct);  // Đọc sản phẩm mới
                if (!newProduct.empty()) cust.product = newProduct; // Nếu có nhập, cập nhật sản phẩm
                cout << "Nhập Số Lượng mới (Enter nếu không thay đổi): "; // Yêu cầu nhập số lượng mới
                string newQuantity;        // Biến lưu số lượng mới
                getline(cin, newQuantity); // Đọc số lượng mới
                if (!newQuantity.empty()) cust.quantity = newQuantity; // Nếu có nhập, cập nhật số lượng
                cout << "Nhập Tổng Tiền mới (Enter nếu không thay đổi): "; // Yêu cầu nhập tổng tiền mới
                string newTotalAmount;     // Biến lưu tổng tiền mới
                getline(cin, newTotalAmount); // Đọc tổng tiền mới
                if (!newTotalAmount.empty()) cust.totalAmount = stod(newTotalAmount); // Nếu có nhập, chuyển đổi và cập nhật tổng tiền
                cout << "Nhập Giảm Giá mới (Enter nếu không thay đổi): "; // Yêu cầu nhập giảm giá mới
                string newDiscount;        // Biến lưu giảm giá mới
                getline(cin, newDiscount); // Đọc giảm giá mới
                if (!newDiscount.empty()) cust.discount = stod(newDiscount); // Nếu có nhập, chuyển đổi và cập nhật giảm giá
                break;                     // Thoát vòng lặp sau khi cập nhật
            }
        }
        if (!found) {                        // Nếu không tìm thấy khách hàng cần cập nhật
            cout << "Không tìm thấy khách hàng có mã " << id << endl; // Thông báo lỗi
            return;                        // Kết thúc hàm
        }
        // Ghi lại file
        ofstream fout(customerFile, ios::trunc); // Mở file khách hàng với chế độ ghi đè (trunc)
        for (auto &cust : customers) {         // Duyệt qua từng khách hàng
            fout << cust.toFileString() << endl; // Ghi thông tin khách hàng vào file
        }
        fout.close();                        // Đóng file
        cout << "Cập nhật khách hàng thành công!" << endl; // Thông báo cập nhật thành công
    }

    // Xóa Customer (Delete)
    void deleteCustomer() {                    // Hàm xóa khách hàng
        ifstream fin(customerFile);            // Mở file khách hàng để đọc
        if (!fin) {                            // Nếu mở file không thành công
            cout << "Không có dữ liệu khách hàng cho ngày: " << currentDate << endl; // Thông báo lỗi
            return;                            // Kết thúc hàm
        }
        vector<Customer> customers;            // Tạo vector lưu danh sách khách hàng
        string line;                           // Biến lưu từng dòng dữ liệu
        while (getline(fin, line)) {           // Đọc từng dòng trong file
            if (line.empty()) continue;        // Nếu dòng trống, bỏ qua
            customers.push_back(Customer::fromFile(line)); // Chuyển đổi dòng dữ liệu thành đối tượng Customer và thêm vào vector
        }
        fin.close();                           // Đóng file đọc

        cout << "Nhập mã khách hàng cần xóa: "; // Yêu cầu nhập mã khách hàng cần xóa
        string id;                           // Biến lưu mã khách hàng
        getline(cin, id);                    // Đọc mã khách hàng từ bàn phím
        bool found = false;                  // Biến đánh dấu đã tìm thấy khách hàng cần xóa hay chưa
        vector<Customer> newCustomers;         // Tạo vector lưu danh sách khách hàng sau khi xóa
        for (auto &cust : customers) {         // Duyệt qua từng khách hàng
            if (cust.id == id) {             // Nếu mã khách hàng khớp
                found = true;                // Đánh dấu đã tìm thấy
                continue;                    // Bỏ qua khách hàng này (xóa)
            }
            newCustomers.push_back(cust);    // Thêm khách hàng không xóa vào vector mới
        }
        if (!found) {                        // Nếu không tìm thấy khách hàng cần xóa
            cout << "Không tìm thấy khách hàng có mã " << id << endl; // Thông báo lỗi
            return;                        // Kết thúc hàm
        }
        ofstream fout(customerFile, ios::trunc); // Mở file khách hàng với chế độ ghi đè
        for (auto &cust : newCustomers) {      // Duyệt qua danh sách khách hàng còn lại
            fout << cust.toFileString() << endl; // Ghi thông tin khách hàng vào file
        }
        fout.close();                        // Đóng file
        cout << "Xóa khách hàng thành công!" << endl; // Thông báo xóa thành công
    }

    //--------------------- Thống kê ---------------------

    // Tính tổng số tiền giảm giá từ dữ liệu khách hàng
    void calculateTotalDiscount() {            // Hàm tính tổng số tiền giảm giá
        ifstream fin(customerFile);            // Mở file khách hàng để đọc
        if (!fin) {                            // Nếu mở file không thành công
            cout << "Không có dữ liệu khách hàng cho ngày: " << currentDate << endl; // Thông báo lỗi
            return;                            // Kết thúc hàm
        }
        double totalDiscount = 0;              // Khởi tạo biến tổng số tiền giảm giá bằng 0
        string line;                           // Biến lưu từng dòng dữ liệu
        while (getline(fin, line)) {           // Đọc từng dòng trong file
            if (line.empty()) continue;        // Nếu dòng trống, bỏ qua
            Customer cust = Customer::fromFile(line); // Tạo đối tượng Customer từ dòng dữ liệu
            totalDiscount += cust.discount;    // Cộng dồn giá trị giảm giá
        }
        fin.close();                           // Đóng file đọc
        cout << "\nTổng Số Tiền Giảm Giá: " << totalDiscount << " đ" << endl; // In ra tổng số tiền giảm giá
    }

    // Tính tổng số tiền hàng (chưa giảm giá)
    void calculateTotalAmount() {              // Hàm tính tổng số tiền hàng (chưa giảm giá)
        ifstream fin(customerFile);            // Mở file khách hàng để đọc
        if (!fin) {                            // Nếu mở file không thành công
            cout << "Không có dữ liệu khách hàng cho ngày: " << currentDate << endl; // Thông báo lỗi
            return;                            // Kết thúc hàm
        }
        double totalAmount = 0;                // Khởi tạo biến tổng số tiền hàng bằng 0
        string line;                           // Biến lưu từng dòng dữ liệu
        while (getline(fin, line)) {           // Đọc từng dòng trong file
            if (line.empty()) continue;        // Nếu dòng trống, bỏ qua
            Customer cust = Customer::fromFile(line); // Tạo đối tượng Customer từ dòng dữ liệu
            totalAmount += cust.totalAmount;   // Cộng dồn tổng số tiền hàng
        }
        fin.close();                           // Đóng file đọc
        cout << "\nTổng Số Tiền Hàng (Chưa Giảm Giá): " << totalAmount << " đ" << endl; // In ra tổng số tiền hàng
    }

    // Tính doanh thu (sau giảm giá)
    void calculateRevenue() {                  // Hàm tính doanh thu (sau giảm giá)
        ifstream fin(customerFile);            // Mở file khách hàng để đọc
        if (!fin) {                            // Nếu mở file không thành công
            cout << "Không có dữ liệu khách hàng cho ngày: " << currentDate << endl; // Thông báo lỗi
            return;                            // Kết thúc hàm
        }
        double revenue = 0;                    // Khởi tạo biến doanh thu bằng 0
        string line;                           // Biến lưu từng dòng dữ liệu
        while (getline(fin, line)) {           // Đọc từng dòng trong file
            if (line.empty()) continue;        // Nếu dòng trống, bỏ qua
            Customer cust = Customer::fromFile(line); // Tạo đối tượng Customer từ dòng dữ liệu
            revenue += (cust.totalAmount - cust.discount); // Tính doanh thu: tổng tiền trừ giảm giá
        }
        fin.close();                           // Đóng file đọc
        cout << "\nDoanh Thu: " << revenue << " đ" << endl; // In ra doanh thu
    }

    //--------------------- Xóa dữ liệu của ngày hiện tại ---------------------
    // (Thao tác này đánh dấu dữ liệu của ngày đã bị xóa, không xóa file gốc)
    void deleteData() {                        // Hàm xóa dữ liệu của ngày hiện tại
        string deleteFileName = "data/del_" + currentDate + ".txt"; // Tạo tên file đánh dấu dữ liệu đã bị xóa
        if (fileExists(deleteFileName)) {      // Kiểm tra nếu file đánh dấu đã tồn tại
            cout << "\nDữ liệu ngày " << currentDate << " đã được xóa trước đó." << endl; // Thông báo dữ liệu đã xóa
            return;                            // Kết thúc hàm
        }
        ofstream fout(deleteFileName);         // Mở file đánh dấu với chế độ ghi
        if (fout) {                            // Nếu mở file thành công
            fout << "Đã xóa dữ liệu cho ngày " << currentDate; // Ghi thông báo vào file
            fout.close();                      // Đóng file
            cout << "\nXóa dữ liệu của ngày " << currentDate << " thành công!" << endl; // Thông báo xóa thành công
        } else {                               // Nếu mở file thất bại
            cout << "\nLỗi khi xóa dữ liệu." << endl; // Thông báo lỗi khi xóa
        }
    }
};

//--------------------- Các chức năng đăng nhập ---------------------

bool adminLogin() {                            // Hàm đăng nhập Admin
    const string username = "admin";           // Tên tài khoản mặc định
    const string password = "123456";          // Mật khẩu mặc định
    string user, pass;                         // Biến lưu thông tin đăng nhập
    int failedAttempts = 0;                    // Biến đếm số lần đăng nhập sai
    while (true) {                             // Vòng lặp đăng nhập liên tục
        cout << "----- Đăng Nhập Admin -----" << endl; // In tiêu đề đăng nhập
        cout << "Tài Khoản: ";                // Yêu cầu nhập tài khoản
        cin >> user;                         // Đọc tài khoản
        cout << "Mật Khẩu: ";                // Yêu cầu nhập mật khẩu
        cin >> pass;                         // Đọc mật khẩu
        cin.ignore();                        // Bỏ qua ký tự newline còn lại
        if (user == username && pass == password) { // Kiểm tra thông tin đăng nhập
            return true;                     // Nếu đúng, trả về true
        } else {                             // Nếu sai
            cout << "Sai Tài Khoản hoặc Mật Khẩu. Vui lòng thử lại." << endl; // Thông báo lỗi đăng nhập
            failedAttempts++;                // Tăng số lần đăng nhập sai
            if (failedAttempts >= 5) {         // Nếu vượt quá 5 lần
                cout << "Quá nhiều lần đăng nhập sai. Vui lòng chờ 15 giây." << endl; // Thông báo chờ
                Sleep(15000);                // Dừng chương trình 15 giây
                failedAttempts = 0;          // Đặt lại số lần đăng nhập sai
            }
        }
    }
    return false;                            // (Không bao giờ đạt đến dòng này)
}

//--------------------- Menu hiển thị ---------------------

void displayMainMenu() {                       // Hàm hiển thị menu chính
    cout << "************************************************************" << endl; // In dòng phân cách
    cout << "            Chào Mừng Admin!" << endl; // In lời chào Admin
    cout << "************************************************************" << endl; // In dòng phân cách
    cout << "1. Quản Lý Dữ Liệu Hôm Nay" << endl;   // Hiển thị lựa chọn 1
    cout << "2. Xem Dữ Liệu Ngày Trước" << endl;    // Hiển thị lựa chọn 2
    cout << "Khác: Thoát Chương Trình" << endl;      // Hiển thị lựa chọn thoát
    cout << "Nhập lựa chọn của bạn: ";              // Yêu cầu nhập lựa chọn
}

void displayTodayManagementMenu() {            // Hàm hiển thị menu quản lý dữ liệu hôm nay
    cout << "-------------------- QUẢN LÝ DỮ LIỆU HÔM NAY --------------------" << endl; // In tiêu đề menu
    cout << "1. Thêm Nhân Viên" << endl;         // Hiển thị lựa chọn thêm nhân viên
    cout << "2. Xem Danh Sách Nhân Viên" << endl;  // Hiển thị lựa chọn xem danh sách nhân viên
    cout << "3. Cập Nhật Nhân Viên" << endl;       // Hiển thị lựa chọn cập nhật nhân viên
    cout << "4. Xóa Nhân Viên" << endl;            // Hiển thị lựa chọn xóa nhân viên
    cout << "5. Thêm Khách Hàng" << endl;          // Hiển thị lựa chọn thêm khách hàng
    cout << "6. Xem Danh Sách Khách Hàng" << endl;   // Hiển thị lựa chọn xem danh sách khách hàng
    cout << "7. Cập Nhật Khách Hàng" << endl;       // Hiển thị lựa chọn cập nhật khách hàng
    cout << "8. Xóa Khách Hàng" << endl;           // Hiển thị lựa chọn xóa khách hàng
    cout << "9. Tổng Số Tiền Giảm Giá" << endl;      // Hiển thị lựa chọn tính tổng số tiền giảm giá
    cout << "10. Tổng Số Tiền Hàng (Chưa Giảm Giá)" << endl; // Hiển thị lựa chọn tính tổng số tiền hàng chưa giảm giá
    cout << "11. Doanh Thu" << endl;              // Hiển thị lựa chọn tính doanh thu
    cout << "12. Thoát về Menu Chính" << endl;     // Hiển thị lựa chọn thoát về menu chính
    cout << "Nhập lựa chọn: ";                  // Yêu cầu nhập lựa chọn
}

void displayPastDataMenu() {                   // Hàm hiển thị menu dữ liệu ngày trước
    cout << "-------------------- XEM DỮ LIỆU NGÀY TRƯỚC --------------------" << endl; // In tiêu đề menu
    cout << "1. Xem Danh Sách Nhân Viên" << endl;  // Hiển thị lựa chọn xem danh sách nhân viên
    cout << "2. Xem Danh Sách Khách Hàng" << endl; // Hiển thị lựa chọn xem danh sách khách hàng
    cout << "3. Tổng Số Tiền Giảm Giá" << endl;    // Hiển thị lựa chọn tính tổng số tiền giảm giá
    cout << "4. Tổng Số Tiền Hàng (Chưa Giảm Giá)" << endl; // Hiển thị lựa chọn tính tổng số tiền hàng chưa giảm giá
    cout << "5. Doanh Thu" << endl;               // Hiển thị lựa chọn tính doanh thu
    cout << "6. Cập Nhật Nhân Viên" << endl;       // Hiển thị lựa chọn cập nhật nhân viên
    cout << "7. Xóa Nhân Viên" << endl;            // Hiển thị lựa chọn xóa nhân viên
    cout << "8. Cập Nhật Khách Hàng" << endl;      // Hiển thị lựa chọn cập nhật khách hàng
    cout << "9. Xóa Khách Hàng" << endl;           // Hiển thị lựa chọn xóa khách hàng
    cout << "10. Xóa Dữ Liệu Ngày Này" << endl;      // Hiển thị lựa chọn xóa dữ liệu của ngày này
    cout << "11. Thoát về Menu Chính" << endl;     // Hiển thị lựa chọn thoát về menu chính
    cout << "Nhập lựa chọn: ";                  // Yêu cầu nhập lựa chọn
}

//--------------------- Hàm main ---------------------

int main() {                                   // Hàm main bắt đầu chương trình
    setlocale(LC_ALL, "vi_VN.UTF-8");          // Cài đặt locale cho tiếng Việt
    SetConsoleOutputCP(65001);                 // Thiết lập mã trang xuất của console thành UTF-8
    srand((unsigned)time(NULL));               // Khởi tạo seed cho hàm rand dựa trên thời gian hiện tại

    createDirectoryIfNotExists("data");        // Tạo thư mục "data" nếu chưa tồn tại

    if (!adminLogin())                         // Gọi hàm đăng nhập Admin; nếu đăng nhập thất bại
        return 1;                              // Thoát chương trình với mã lỗi 1

    clearScreen();                             // Xoá màn hình console
    ManagementSystem systemManager;            // Tạo đối tượng quản lý hệ thống dữ liệu
    int mainChoice;                            // Biến lưu lựa chọn của menu chính
    do {                                       // Vòng lặp menu chính
        displayMainMenu();                     // Hiển thị menu chính
        cin >> mainChoice;                     // Đọc lựa chọn của người dùng
        cin.ignore();                          // Bỏ qua ký tự newline còn lại
        if (mainChoice == 1) {                   // Nếu người dùng chọn "Quản Lý Dữ Liệu Hôm Nay"
            systemManager.changeDate(getCurrentDate()); // Cập nhật ngày quản lý là ngày hiện tại
            int managementChoice;              // Biến lưu lựa chọn của menu quản lý dữ liệu hôm nay
            do {                               // Vòng lặp menu quản lý dữ liệu hôm nay
                clearScreen();                 // Xoá màn hình
                displayTodayManagementMenu();  // Hiển thị menu quản lý dữ liệu hôm nay
                cin >> managementChoice;       // Đọc lựa chọn của người dùng
                cin.ignore();                  // Bỏ qua ký tự newline còn lại
                switch(managementChoice) {     // Xét các trường hợp của lựa chọn
                    case 1: {                // Nếu chọn "Thêm Nhân Viên"
                        int count;           // Biến lưu số lượng nhân viên cần thêm
                        cout << "Nhập số lượng nhân viên cần thêm: "; // Yêu cầu nhập số lượng
                        cin >> count;        // Đọc số lượng từ bàn phím
                        cin.ignore();        // Bỏ qua ký tự newline còn lại
                        systemManager.addEmployee(count); // Gọi hàm thêm nhân viên với số lượng đã nhập
                        showWaitMessage("Quay lại menu", 2); // Hiển thị thông báo chờ trước khi quay lại menu
                        break;               // Thoát case
                    }
                    case 2:                  // Nếu chọn "Xem Danh Sách Nhân Viên"
                        systemManager.viewEmployees(); // Gọi hàm xem danh sách nhân viên
                        system("pause");     // Dừng chương trình cho đến khi người dùng nhấn phím
                        break;               // Thoát case
                    case 3:                  // Nếu chọn "Cập Nhật Nhân Viên"
                        systemManager.updateEmployee(); // Gọi hàm cập nhật nhân viên
                        system("pause");     // Dừng chương trình
                        break;               // Thoát case
                    case 4:                  // Nếu chọn "Xóa Nhân Viên"
                        systemManager.deleteEmployee(); // Gọi hàm xóa nhân viên
                        system("pause");     // Dừng chương trình
                        break;               // Thoát case
                    case 5: {                // Nếu chọn "Thêm Khách Hàng"
                        int count;           // Biến lưu số lượng khách hàng cần thêm
                        cout << "Nhập số lượng khách hàng cần thêm: "; // Yêu cầu nhập số lượng
                        cin >> count;        // Đọc số lượng từ bàn phím
                        cin.ignore();        // Bỏ qua ký tự newline còn lại
                        systemManager.addCustomer(count); // Gọi hàm thêm khách hàng
                        showWaitMessage("Quay lại menu", 2); // Hiển thị thông báo chờ
                        break;               // Thoát case
                    }
                    case 6:                  // Nếu chọn "Xem Danh Sách Khách Hàng"
                        systemManager.viewCustomers(); // Gọi hàm xem danh sách khách hàng
                        system("pause");     // Dừng chương trình
                        break;               // Thoát case
                    case 7:                  // Nếu chọn "Cập Nhật Khách Hàng"
                        systemManager.updateCustomer(); // Gọi hàm cập nhật khách hàng
                        system("pause");     // Dừng chương trình
                        break;               // Thoát case
                    case 8:                  // Nếu chọn "Xóa Khách Hàng"
                        systemManager.deleteCustomer(); // Gọi hàm xóa khách hàng
                        system("pause");     // Dừng chương trình
                        break;               // Thoát case
                    case 9:                  // Nếu chọn "Tổng Số Tiền Giảm Giá"
                        systemManager.calculateTotalDiscount(); // Gọi hàm tính tổng số tiền giảm giá
                        system("pause");     // Dừng chương trình
                        break;               // Thoát case
                    case 10:                 // Nếu chọn "Tổng Số Tiền Hàng (Chưa Giảm Giá)"
                        systemManager.calculateTotalAmount(); // Gọi hàm tính tổng số tiền hàng chưa giảm giá
                        system("pause");     // Dừng chương trình
                        break;               // Thoát case
                    case 11:                 // Nếu chọn "Doanh Thu"
                        systemManager.calculateRevenue(); // Gọi hàm tính doanh thu
                        system("pause");     // Dừng chương trình
                        break;               // Thoát case
                    case 12:                 // Nếu chọn "Thoát về Menu Chính"
                        cout << "Thoát về Menu Chính..." << endl; // Thông báo thoát về menu chính
                        break;               // Thoát case
                    default:                 // Nếu nhập lựa chọn không hợp lệ
                        cout << "Lựa chọn không hợp lệ. Vui lòng thử lại." << endl; // Thông báo lỗi
                        break;               // Thoát case
                }
            } while(managementChoice != 12);        // Lặp cho đến khi chọn thoát về menu chính
        }
        else if (mainChoice == 2) {                   // Nếu người dùng chọn "Xem Dữ Liệu Ngày Trước"
            int day, month, year;                    // Khai báo biến cho ngày, tháng, năm
            cout << "Nhập năm (>=2000): ";           // Yêu cầu nhập năm
            cin >> year;                             // Đọc năm từ bàn phím
            cin.ignore();                            // Bỏ qua ký tự newline
            cout << "Nhập tháng (1-12): ";            // Yêu cầu nhập tháng
            cin >> month;                            // Đọc tháng từ bàn phím
            cin.ignore();                            // Bỏ qua ký tự newline
            int maxDay = 31;                         // Giả sử số ngày tối đa là 31
            if (month == 2) {                        // Nếu tháng 2
                if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)) // Kiểm tra năm nhuận
                    maxDay = 29;                     // Nếu năm nhuận, số ngày là 29
                else
                    maxDay = 28;                     // Nếu không, số ngày là 28
            } else if (month == 4 || month == 6 || month == 9 || month == 11) { // Nếu tháng 4, 6, 9, 11
                maxDay = 30;                         // Số ngày là 30
            }
            cout << "Nhập ngày (1-" << maxDay << "): "; // Yêu cầu nhập ngày, giới hạn theo maxDay
            cin >> day;                              // Đọc ngày từ bàn phím
            cin.ignore();                            // Bỏ qua ký tự newline
            ostringstream oss;                       // Tạo luồng xuất chuỗi để định dạng ngày
            oss << day << "_" << month << "_" << year; // Định dạng thành chuỗi "dd_mm_yyyy"
            systemManager.changeDate(oss.str());     // Cập nhật ngày quản lý dữ liệu theo ngày vừa nhập
            int pastChoice;                          // Biến lưu lựa chọn của menu dữ liệu ngày trước
            do {                                     // Vòng lặp menu dữ liệu ngày trước
                clearScreen();                       // Xoá màn hình
                displayPastDataMenu();               // Hiển thị menu dữ liệu ngày trước
                cin >> pastChoice;                   // Đọc lựa chọn từ người dùng
                cin.ignore();                        // Bỏ qua ký tự newline
                switch(pastChoice) {                 // Xét lựa chọn của người dùng
                    case 1:                        // Nếu chọn "Xem Danh Sách Nhân Viên"
                        systemManager.viewEmployees(); // Gọi hàm xem danh sách nhân viên
                        system("pause");           // Dừng chương trình
                        break;                     // Thoát case
                    case 2:                        // Nếu chọn "Xem Danh Sách Khách Hàng"
                        systemManager.viewCustomers(); // Gọi hàm xem danh sách khách hàng
                        system("pause");           // Dừng chương trình
                        break;                     // Thoát case
                    case 3:                        // Nếu chọn "Tổng Số Tiền Giảm Giá"
                        systemManager.calculateTotalDiscount(); // Gọi hàm tính tổng số tiền giảm giá
                        system("pause");           // Dừng chương trình
                        break;                     // Thoát case
                    case 4:                        // Nếu chọn "Tổng Số Tiền Hàng (Chưa Giảm Giá)"
                        systemManager.calculateTotalAmount(); // Gọi hàm tính tổng số tiền hàng chưa giảm giá
                        system("pause");           // Dừng chương trình
                        break;                     // Thoát case
                    case 5:                        // Nếu chọn "Doanh Thu"
                        systemManager.calculateRevenue(); // Gọi hàm tính doanh thu
                        system("pause");           // Dừng chương trình
                        break;                     // Thoát case
                    case 6:                        // Nếu chọn "Cập Nhật Nhân Viên"
                        systemManager.updateEmployee(); // Gọi hàm cập nhật nhân viên
                        system("pause");           // Dừng chương trình
                        break;                     // Thoát case
                    case 7:                        // Nếu chọn "Xóa Nhân Viên"
                        systemManager.deleteEmployee(); // Gọi hàm xóa nhân viên
                        system("pause");           // Dừng chương trình
                        break;                     // Thoát case
                    case 8:                        // Nếu chọn "Cập Nhật Khách Hàng"
                        systemManager.updateCustomer(); // Gọi hàm cập nhật khách hàng
                        system("pause");           // Dừng chương trình
                        break;                     // Thoát case
                    case 9:                        // Nếu chọn "Xóa Khách Hàng"
                        systemManager.deleteCustomer(); // Gọi hàm xóa khách hàng
                        system("pause");           // Dừng chương trình
                        break;                     // Thoát case
                    case 10:                       // Nếu chọn "Xóa Dữ Liệu Ngày Này"
                        systemManager.deleteData(); // Gọi hàm xóa dữ liệu của ngày hiện tại
                        system("pause");           // Dừng chương trình
                        break;                     // Thoát case
                    case 11:                       // Nếu chọn "Thoát về Menu Chính"
                        cout << "Thoát về Menu Chính..." << endl; // Thông báo thoát về menu chính
                        break;                     // Thoát case
                    default:                       // Nếu lựa chọn không hợp lệ
                        cout << "Lựa chọn không hợp lệ. Vui lòng thử lại." << endl; // Thông báo lỗi lựa chọn
                        break;                     // Thoát case
                }
            } while(pastChoice != 11);             // Lặp cho đến khi người dùng chọn thoát về menu chính
        }
        else {                                     // Nếu lựa chọn không phải 1 hay 2
            cout << "Thoát chương trình. Hẹn gặp lại!" << endl; // Thông báo thoát chương trình
            break;                                 // Thoát vòng lặp menu chính
        }
    } while(true);                               // Vòng lặp vô hạn cho menu chính

    return 0;                                    // Kết thúc chương trình, trả về 0
}
