#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct {
    char accountId[20];
    char fullName[50];
    char phone[15];
    double balance;
    int status; 
} AddAccount;
typedef struct{
	char transId[20];
	char senderId[20];
	char receiverId[20];
	double amount;
	char type[10];
	char date[20];
}Transaction;
void existingAccount(AddAccount account[], int *length){
	*length =15;
	AddAccount sample[15] = {
		{"001","Nguyen Van D","0912345671", 1000,1},
        {"002", "Tran Thi B", "0912345672", 1500, 1},
        {"003", "Le Van C", "0912345673", 2000, 1},
        {"004", "Pham Thi D", "0912345674", 2500, 1},
        {"005", "Hoang Van E", "0912345675", 3000, 1},
        {"006", "Nguyen Thi F", "0912345676", 3500, 1},
        {"007", "Tran Van G", "0912345677", 4000, 1},
        {"008", "Le Thi H", "0912345678", 4500, 1},
        {"009", "Pham Van I", "0912345679", 5000, 1},
        {"010", "Nguyen Van J", "0912345680", 5500, 1},
        {"011", "Tran Thi K", "0912345681", 6000, 1},
        {"012", "Le Van L", "0912345682", 6500, 1},
        {"013", "Pham Thi M", "0912345683", 7000, 1},
        {"014", "Hoang Van N", "0912345684", 7500, 1},
        {"015", "Nguyen Thi O", "0912345685", 8000, 1}
    };
    for(int i = 0; i <15;i++)
        account[i] = sample[i];
	
}
int isSpace(char *str) {
    if (str == NULL || strlen(str) == 0) return 1;
    for (int i = 0; i < strlen(str); i++) {
        if (!isspace(str[i])) return 0;
    }
    return 1;
}

void readLine(char *buf, int size) {
    if (fgets(buf, size, stdin) != NULL) {
        buf[strcspn(buf, "\n")] = '\0';
    }
}

int inputMenuChoice(const char suggest[], int min, int max) {
    char string[20];
    int number;
    while (1) {
        printf("%s (%d - %d): ", suggest, min, max);
        fgets(string, sizeof(string), stdin);
        string[strcspn(string, "\n")] = 0;

        if (strlen(string) == 0) {
            printf("Loi: Vui long nhap so!\n");
            continue;
        }

        int isDigit = 1;
        for (int i = 0; i < strlen(string); i++)
            if (!isdigit(string[i])) { isDigit = 0; break; }

        if (!isDigit) {
            printf("Loi: Chi nhap so!\n");
            continue;
        }

        number = atoi(string);
        if (number >= min && number <= max) return number;
        printf("Chi duoc nhap tu %d den %d\n", min, max);
    }
}

int isIDDuplicate(AddAccount account[], int length, char id[]) {
    for (int i = 0; i < length; i++)
        if (strcmp(account[i].accountId, id) == 0) return 1;
    return 0;
}
int isPhoneDuplicate(AddAccount account[], int length, char phone[], int ignoreIndex) {
    for (int i = 0; i < length; i++)
        if (i != ignoreIndex && strcmp(account[i].phone, phone) == 0) return 1;
    return 0;
}

int isValidName(char name[]) {
    for (int i = 0; i < (int)strlen(name); i++)
        if (!isalpha((unsigned char)name[i]) && name[i] != ' ') return 0;
    return 1;
}

// Kiểm tra ID hợp lệ
int isValidID(char id[]) {
    if (strlen(id) == 0) return 0; 
    for (int i = 0; i < (int)strlen(id); i++) {
        if (!isdigit((unsigned char)id[i])) return 0; 
    }
    return 1;
}
// kiem tra phone 
int isValidPhone(char phone[]) {
    if (phone == NULL || strlen(phone) == 0) return 0;
    int len = strlen(phone);
    if (len > 10) return 0;  

    for (int i = 0; i < len; i++) {
        if (!isdigit((unsigned char)phone[i]))return 0;
    }
    return 1;
}

// Thêm tài khoản
void enterCustomerInformation(AddAccount account[], int *length) {
    int size = inputMenuChoice("Nhap so luong tai khoan muon them", 1, 100);

    for (int i = 0; i < size; i++) {
        AddAccount temp;
        printf("\n=== Nhap tai khoan thu %d ===\n", i + 1);

        // Nhập ID
        while (1) {
            printf("Nhap ID tai khoan: ");
            fflush(stdout);
            readLine(temp.accountId, sizeof(temp.accountId));

            if (strlen(temp.accountId) == 0) {
                printf("Loi: ID khong duoc rong!\n");
                continue;
            }
            if (!isValidID(temp.accountId)) {
                printf("Loi: ID khong duoc nhan vui long nhap lai!\n");
                continue;
            }
            if (isIDDuplicate(account, *length, temp.accountId)) {
                printf("Loi: ID da ton tai!\n");
                continue;
            }
            break;
        }

        // Nhập Họ Tên
        while (1) {
            printf("Nhap ho ten: ");
            fflush(stdout);
            readLine(temp.fullName, sizeof(temp.fullName));

            if (isSpace(temp.fullName)) {
                printf("Loi: Ten khong duoc de trong.\n");
                continue;
            }
            if (!isValidName(temp.fullName)) {
                printf("Loi: Ho ten chi duoc chua chu cai!\n");
                continue;
            }
            break;
        }

        // Nhập SDT
        while (1) {
        printf("Nhap so dien thoai (1-10 chu so): ");
        fflush(stdout);
        readLine(temp.phone, sizeof(temp.phone));

        if (!isValidPhone(temp.phone)) {
        printf("Loi: SDT khong hop le! Vui long nhap lai.\n");
        continue;
        }

        if (isPhoneDuplicate(account, *length, temp.phone, -1)) {
        printf("Loi: SDT da ton tai!\n");
        continue;
        }
        break;
        }
        temp.balance = 0.0;
        temp.status = 1;

        account[*length] = temp;
        (*length)++;

        printf("Them tai khoan thanh cong!\n");
    }
}

// Tìm index theo ID
int findIndexByID(AddAccount account[], int length, char accountId[]) {
    for (int i = 0; i < length; i++)
        if (strcmp(account[i].accountId, accountId) == 0) return i;
    return -1;
}

// Cập nhật thông tin tài khoản
void updateAccount(AddAccount account[], int length) {
    if (length == 0) {
        printf("Vui long them it nhat 1 tai khoan truoc!\n");
        return;
    }

    char idUpdate[20];
    printf("Nhap ID tai khoan can cap nhat: ");
    fflush(stdout);
    readLine(idUpdate, sizeof(idUpdate));

    int index = findIndexByID(account, length, idUpdate);
    if (index == -1) {
        printf("Loi: khong tim thay tai khoan!\n");
        return;
    }

    printf("\n---Thong tin hien tai---\n");
    printf("ID    : %s\n", account[index].accountId);
    printf("HoTen : %s\n", account[index].fullName);
    printf("SDT   : %s\n", account[index].phone);
    printf("------------------------\n");

    char newName[50], newPhone[15];
    printf("Nhap ten moi (bo trong neu giu nguyen): ");
    fflush(stdout);
    readLine(newName, sizeof(newName));

    if (strlen(newName) > 0) {
        if (isSpace(newName)) {
            printf("Loi: Ten khong duoc toan khoang trang!\n");
            return;
        }
        if (!isValidName(newName)) {
            printf("Loi: Ten moi khong hop le! (chi duoc co chu cai va khoang trang hop le)\n");
            return;
        }
        strcpy(account[index].fullName, newName);
    }

    printf("Nhap SDT moi (bo trong neu giu nguyen): ");
    fflush(stdout);
    readLine(newPhone, sizeof(newPhone));

    if (strlen(newPhone) > 0) {

        for (int i = 0; i < strlen(newPhone); i++) {
            if (isspace((unsigned char)newPhone[i])) {
                printf("Loi: SDT khong duoc chua khoang trang!\n");
                return;
            }
        }

        for (int i = 0; i < strlen(newPhone); i++) {
            if (!isdigit(newPhone[i])) {
                printf("Loi: SDT chi duoc chua so 0-9!\n");
                return;
            }
        }

        if (isPhoneDuplicate(account, length, newPhone, index)) {
            printf("Loi: SDT da ton tai!\n");
            return;
        }

        strcpy(account[index].phone, newPhone);
    }

    printf("Cap nhat thanh cong!\n");
}


// Quản lý trạng thái: khóa/xóa luôn
void manageStatus(AddAccount account[], int *length) {
	
    if (*length == 0) {
        printf("Vui long them it nhat 1 tai khoan truoc!\n");
        return;
    }

    char idInput[20];
    printf("Nhap ID tai khoan can quan ly: ");
    fflush(stdout);
    readLine(idInput, sizeof(idInput));

    int index = findIndexByID(account, *length, idInput);
    if (index == -1) {
        printf("Loi: khong tim thay tai khoan!\n");
        return;
    }

    printf("\nID: %s\nHo Ten: %s\nSDT: %s\nSo du: %.2lf\nTrang thai: %s\n",
           account[index].accountId,
           account[index].fullName,
           account[index].phone,
           account[index].balance,
           account[index].status == 1 ? "1" : "0");

    printf("\nLua chon thao tac:\n1. Khoa tai khoan\n2. Xoa tai khoan\n0. Huy\n");
    int choice = inputMenuChoice("Nhap lua chon", 0, 2);

    switch(choice) {
        case 1:
            if (account[index].status == 1) {
                account[index].status = 0;
                printf("Khoa tai khoan thanh cong!\n");
            } else {
                printf("Tai khoan da bi khoa!\n");
            }
            break;
        case 2:
            for (int i = index; i < *length - 1; i++)
                account[i] = account[i + 1];
            (*length)--;
            printf("Xoa tai khoan thanh cong!\n");
            break;
        case 0:
            printf("Huy thao tac!\n");
            break;
        default:
            printf("Lua chon khong hop le!\n");
    }
}

// Tìm kiếm tài khoản
void searchAccount(AddAccount account[], int length) {
    if (length == 0) {
        printf("Vui long them it nhat 1 tai khoan truoc khi tim kiem!\n");
        return;
    }

    printf("\n== TIM KIEM TAI KHOAN ==\n1. Tim theo ID\n2. Tim theo Ten\n");
    int choice = inputMenuChoice("Nhap lua chon", 1, 2);

    if (choice == 1) {
        char id[20];
        printf("Nhap ID can tim: ");
        readLine(id, sizeof(id));

        int found = 0;
        for (int i = 0; i < length; i++) {
            if (strcmp(account[i].accountId, id) == 0) {
                printf("ID: %s | Ten: %s | SDT: %s | Balance: %.2lf | Status: %s\n",
                       account[i].accountId, account[i].fullName,
                       account[i].phone, account[i].balance,
                       account[i].status == 1 ? "1" : "0  ");
                found = 1;
                break;
            }
        }
        if (!found) printf("Khong tim thay tai khoan voi ID nay!\n");
    } else if (choice == 2) {
        char name[50];
        printf("Nhap ten can tim: ");
        readLine(name, sizeof(name));

        int found = 0;
        for (int i = 0; i < length; i++) {
            if (strstr(account[i].fullName, name) != NULL) {
                printf("ID: %s | Ten: %s | SDT: %s | Balance: %.2lf | Status: %s\n",
                       account[i].accountId, account[i].fullName,
                       account[i].phone, account[i].balance,
                       account[i].status == 1 ? "1" : "0");
                found = 1;
            }
        }
        if (!found) printf("Khong tim thay tai khoan voi ten nay!\n");
    }
}
//Danh sách (phân / trang)
void accountsPagination(AddAccount account[], int length){
    if (length == 0){
        printf("Chua co tai khoan nao !\n");
        return;
    }

    char buf[50];
    int page_number, page_size;

    while (1) {
        printf("Nhap so trang: ");
        if (!fgets(buf, sizeof(buf), stdin)) continue;
        buf[strcspn(buf, "\n")] = '\0';

        int valid = 1;
        for (size_t i = 0; i < strlen(buf); i++) {
            if (!isdigit((unsigned char)buf[i])) { 
                valid = 0; 
                break; 
            }
        }

        if (!valid) {
            printf("Loi: Ban phai nhap so!\n");
            continue;
        }

        page_number = atoi(buf);
        if (page_number <= 0) {
            printf("Loi: So trang phai lon hon 0!\n");
            continue;
        }
        break;
    }

    while (1) {
        printf("Nhap so luong dong muon in (toi da 10): ");
        if (!fgets(buf, sizeof(buf), stdin)) continue;
        buf[strcspn(buf, "\n")] = '\0';

        int valid = 1;
        for (size_t i = 0; i < strlen(buf); i++) {
            if (!isdigit((unsigned char)buf[i])) { 
                valid = 0; 
                break; 
            }
        }

        if (!valid) {
            printf("Loi: Ban phai nhap so!\n");
            continue;
        }

        page_size = atoi(buf);
        if (page_size <= 0 || page_size > 10) {
            printf("Loi: So dong phai tu 1 den 10!\n");
            continue;
        }
        break;
    }

    int start = (page_number - 1) * page_size;
    int end = start + page_size;

    if (start >= length) {
        printf("Khong co du lieu o trang nay!\n");
        return;
    }
    if (end > length) end = length;

    printf("\n==== Trang %d ====\n", page_number);
    for (int i = start; i < end; i++) {
        printf("%d. ID: %s | Ten: %s | Phone: %s | Balance: %.2lf | Status: %d\n",
               i + 1,
               account[i].accountId,
               account[i].fullName,
               account[i].phone,
               account[i].balance,
               account[i].status);
    }
}
//sap xep
char* getLastName(char fullName[]) {
    char *last = strrchr(fullName, ' ');
    if (last == NULL) return fullName; 
    return last + 1; 
}

void sortAccount(AddAccount account[], int length) {
    if (length == 0) {
        printf("Khong co du lieu can sap xep!\n");
        return;
    }

    printf("\n=== SAP XEP TAI KHOAN ===\n");
    printf("[1] Theo so du giam dan\n");
    printf("[2] Theo ten A-Z\n");
    int choice = inputMenuChoice("Nhap lua chon", 1, 2);

    switch (choice) {
        case 1:
            for (int i = 0; i < length - 1; i++) {
                for (int j = i + 1; j < length; j++) {
                    if (account[i].balance < account[j].balance) {
                        AddAccount tmp = account[i];
                        account[i] = account[j];
                        account[j] = tmp;
                    }
                }
            }
            printf("Da sap xep theo so du giam dan!\n");
            break;
        case 2:
        	for (int i = 0; i < length - 1; i++) {
                 for (int j = i + 1; j < length; j++) {
                    if (strcmp(getLastName(account[i].fullName),
                       getLastName(account[j].fullName)) > 0) {

                        AddAccount tmp = account[i];
                        account[i] = account[j];
                        account[j] = tmp;
                    }
                }
            }
            printf("Da sap xep theo ten rieng (A-Z)!\n");
            break;
        default:
            printf("Lua chon khong hop le!\n");
    }
}
//Giao dich chuyen khoan 
void transferMoney(AddAccount account[], int length, Transaction tran[], int *transLength) {
    if (length == 0) {
        printf("Khong co du lieu can chuyen khoan!\n");
        return;
    }

    char senderId[20], receiverId[20];
    int senderIndex, receiverIndex;
    double amount;

    // Nhap ID nguoi gui
    while (1) {
        printf("Nhap ID nguoi gui: ");
        readLine(senderId, sizeof(senderId));

        if (!isValidID(senderId)) {
            printf("Loi: ID khong hop le, vui long nhap lai!\n");
            continue;
        }

        senderIndex = findIndexByID(account, length, senderId);
        if (senderIndex == -1) {
            printf("Loi: Tai khoan khong ton tai, vui long nhap lai!\n");
            continue;
        }

        if (account[senderIndex].status != 1) {
            printf("Loi: Tai khoan dang bi khoa, vui long chon tai khoan khac!\n");
            continue;
        }

        break;
    }

    // Nhap ID nguoi nhan
    while (1) {
        printf("Nhap ID nguoi nhan: ");
        readLine(receiverId, sizeof(receiverId));

        if (!isValidID(receiverId)) {
            printf("Loi: ID khong hop le, vui long nhap lai!\n");
            continue;
        }

        receiverIndex = findIndexByID(account, length, receiverId);
        if (receiverIndex == -1) {
            printf("Loi: Tai khoan khong ton tai, vui long nhap lai!\n");
            continue;
        }

        if (strcmp(senderId, receiverId) == 0) {
            printf("Loi: Khong the chuyen tien cho chinh minh, vui long nhap lai!\n");
            continue;
        }

        break;
    }

    // Nhap so tien
    char buf[50];
    while (1) {
        printf("Nhap so tien can chuyen: ");
        readLine(buf, sizeof(buf));

        int valid = 1, dotCount = 0;
        for (size_t i = 0; i < strlen(buf); i++) {
            if (!isdigit((unsigned char)buf[i])) {
                if (buf[i] == '.' && dotCount == 0) dotCount++;
                else valid = 0;
            }
        }

        if (!valid || strlen(buf) == 0) {
            printf("Loi: Vui long nhap so tien hop le (chi nhap so)!\n");
            continue;
        }

        amount = atof(buf);
        if (amount <= 0) {
            printf("So tien phai lon hon 0!\n");
            continue;
        }

        if (amount > account[senderIndex].balance) {
            printf("Loi: So du khong du!\n");
            continue;
        }

        break;
    }

    // Cap nhat so du
    account[senderIndex].balance -= amount;
    account[receiverIndex].balance += amount;

    // Luu giao dich
    Transaction t;
    sprintf(t.transId, "T%03d", *transLength + 1);
    strcpy(t.senderId, senderId);
    strcpy(t.receiverId, receiverId);
    t.amount = amount;

    tran[*transLength] = t;
    (*transLength)++;

    printf("Chuyen khoan thanh cong!\n");
}

// lich su giao dich 
void showTransactionHistory(AddAccount account[], int length,Transaction tran[],int *transLength) {
    if (length == 0) {
        printf("He thong chua co tai khoan nao!\n");
        return;
    }

    char targetId[20];
    while (1) {
        printf("Nhap ID tai khoan can xem lich su: ");
        readLine(targetId, sizeof(targetId));

        if (!isValidID(targetId)) {
            printf("Loi: Vui long nhap lai !\n");
            continue;
        }
        break;
    }

    int accIndex = findIndexByID(account, length, targetId);
    if (accIndex == -1) {
        printf("Loi: Tai khoan khong ton tai!\n");
        return;
    }
// kiem tra giao dich
    int found = 0;
    printf("\n===== LICH SU GIAO DICH CUA TAI KHOAN %s =====\n", targetId);

    for (int i = 0; i < *transLength; i++) {
        if (strcmp(tran[i].senderId, targetId) == 0 ||
            strcmp(tran[i].receiverId, targetId) == 0) 
        {
            found = 1;
            printf("%d. Ma GD: %s | ", i + 1, tran[i].transId);

            if (strcmp(tran[i].senderId, targetId) == 0) {
                printf("Loai: OUT | Gui den: %s | So tien: %.2f\n",
                       tran[i].receiverId, tran[i].amount);
            } else {
                printf("Loai: IN  | Nhan tu: %s | So tien: %.2f\n",
                       tran[i].senderId, tran[i].amount);
            }
        }
    }

    if (!found) {
        printf("Khong co giao dich nao!\n");
    }
    return;
}
int main() {
    AddAccount account[100];
    int length = 0;
    existingAccount(account, &length);
    int choice;
    Transaction tran[100];
    int transLength = 0;

    do {
        printf("\n||================ MENU BANK MANAGEMENT ================||\n");
        printf("|| 01. Add new account                                  ||\n");
        printf("|| 02. Update information                               ||\n");
        printf("|| 03. Manage status (Lock/Delete)                      ||\n");
        printf("|| 04. Lookup (Search)                                  ||\n");
        printf("|| 05. List (pagination)                                ||\n");
        printf("|| 06. Sort list                                        ||\n");
        printf("|| 07. Transaction Transfer                             ||\n");
        printf("|| 08. Transaction history                              ||\n");
        printf("|| 09. Exit                                             ||\n");
        printf("||======================================================||\n");

        choice = inputMenuChoice("Enter your choice", 1, 9);

        switch(choice) {
            case 1: enterCustomerInformation(account, &length); break;
            case 2: updateAccount(account, length); break;
            case 3: manageStatus(account, &length); break;
            case 4: searchAccount(account, length); break;
            case 5: accountsPagination(account,length); break;
            case 6: sortAccount(account, length); break;
            case 7: transferMoney(account,length,tran,&transLength); break;
            case 8: showTransactionHistory(account, length, tran, &transLength); break;
            case 9: printf("Thoat chuong trinh.\n"); break;
            default: printf("Lua chon khong hop le!\n");
        }
    } while(choice != 9);

    return 0;
}
