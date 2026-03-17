#include <iostream>
#include <cstdio>
using namespace std;

struct Karyawan{
    int id;
    char nama[50];
};

struct Barang{
    char nama[50];
    int harga;
    int stok;
};

int bandingString(const char a[], const char b[]){
    int i=0;
    while(a[i] != '\0' && b[i] != '\0'){
        if(a[i] != b[i])
            return a[i]-b[i];
        i++;
    }
    return a[i]-b[i];
}

void pause(){
    cout<<"\nPress any key to continue...";
    getchar();
    getchar();
    system("cls");
}

void success(){
    cout<<"\nData berhasil disimpan!\n";
    pause();
}

void bubbleSort(Barang b[], int n){
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(b[j].harga > b[j+1].harga){
                Barang temp=b[j];
                b[j]=b[j+1];
                b[j+1]=temp;
            }
        }
    }
}

void quickSort(Barang b[], int low, int high){

    int i=low;
    int j=high;
    int pivot=b[(low+high)/2].harga;

    while(i<=j){

        while(b[i].harga > pivot) i++;
        while(b[j].harga < pivot) j--;

        if(i<=j){
            Barang temp=b[i];
            b[i]=b[j];
            b[j]=temp;
            i++;
            j--;
        }
    }

    if(low<j) quickSort(b,low,j);
    if(i<high) quickSort(b,i,high);
}

void sortNama(Barang b[], int n){

    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){

            if(bandingString(b[j].nama,b[j+1].nama) > 0){

                Barang temp=b[j];
                b[j]=b[j+1];
                b[j+1]=temp;

            }
        }
    }
}

void tambahKaryawan(){

    FILE *fp=fopen("karyawan.txt","a");

    if(fp==NULL){
        cout<<"\nFile error\n";
        return;
    }

    int n;

    cout<<"\n=== Tambah Karyawan ===\n";
    cout<<"Jumlah karyawan: ";
    cin>>n;

    Karyawan k[n];
    Karyawan *ptr=k;

    for(int i=0;i<n;i++){
		
		
        cout<<"ID karyawan: ";
        cin>>(ptr+i)->id;

        cout<<"Nama karyawan: ";
        cin>>(ptr+i)->nama;
        cout<<" \n";

        fprintf(fp,"%d %s\n",(ptr+i)->id,(ptr+i)->nama);
    }

    fclose(fp);
    success();
}

void lihatKaryawan(){

    FILE *fp=fopen("karyawan.txt","r");

    if(fp==NULL){
        cout<<"\nData kosong\n";
        pause();
        return;
    }

    Karyawan k;
    int i=1;

    cout<<"\n=== Data Karyawan ===\n";

    while(fscanf(fp,"%d %s",&k.id,k.nama)!=EOF){
		
		cout<<"Karyawan Ke-"<<i<<endl;
        cout<<"ID : "<<k.id<<endl;
        cout<<"Nama : "<<k.nama<<endl;
        i++;
    }

    fclose(fp);
    pause();
}

void cariKaryawan(){

    FILE *fp=fopen("karyawan.txt","r");

    if(fp==NULL){
        cout<<"\nData kosong\n";
        pause();
        return;
    }

    int id;
    cout<<"\n=== Cari Karyawan ===\n";
    cout<<"Masukkan ID: ";
    cin>>id;

    Karyawan k;
    bool found=false;

    while(fscanf(fp,"%d %s",&k.id,k.nama)!=EOF){

        if(k.id==id){

            cout<<"\nData ditemukan!\n";
            cout<<"ID : "<<k.id<<endl;
            cout<<"Nama : "<<k.nama<<endl;
            found=true;
        }
    }

    if(!found)
        cout<<"Data tidak ditemukan\n";

    fclose(fp);
    pause();
}

void tambahBarang(){

    FILE *fp=fopen("barang.txt","a");

    if(fp==NULL){
        cout<<"File error\n";
        return;
    }

    int n;

    cout<<"=== Tambah Barang ===\n";
    cout<<"Jumlah barang: ";
    cin>>n;

    Barang b[n];
    Barang *ptr=b;

    cin.ignore();

    for(int i=0;i<n;i++){

        cout<<"\nBarang ke-"<<i+1<<endl;

        cout<<"Nama Barang: ";
        cin.getline((ptr+i)->nama,50);

        cout<<"Harga Barang: ";
        cin>>(ptr+i)->harga;

        cout<<"Stok Barang: ";
        cin>>(ptr+i)->stok;
        cout<<" \n";
        cin.ignore();

        fprintf(fp,"%s|%d|%d\n",(ptr+i)->nama,(ptr+i)->harga,(ptr+i)->stok);
    }

    fclose(fp);
    success();
}

 void lihatBarang(){

    FILE *fp=fopen("barang.txt","r");

    if(fp==NULL){
        cout<<"Data kosong\n";
        pause();
        return;
    }

    Barang b[100];
    int n=0;

    while(fscanf(fp,"%[^|]|%d|%d\n",b[n].nama,&b[n].harga,&b[n].stok)!=EOF){
        n++;
    }

    fclose(fp);

    int pilih;
    
    cout<<"\n=== Lihat Barang ===\n";
    cout<<"1 Ascending\n";
    cout<<"2 Descending\n";
    cout<<"======================\n";
    cout<<"Pilih: ";
    cin>>pilih;

    if(pilih==1)
        bubbleSort(b,n);
    else
        quickSort(b,0,n-1);

    cout<<"\n=== Data Barang ===\n";

    for(int i=0;i<n;i++){
		
		cout<<"\nBarang ke-"<<i+1<<endl;
        cout<<"Nama : "<<b[i].nama<<endl;
        cout<<"Harga : "<<b[i].harga<<endl;
        cout<<"Stok : "<<b[i].stok<<endl;
        cout<<"\n-----------------\n";
    }

    pause();
}

void editBarang(){

    FILE *fp=fopen("barang.txt","r");

    if(fp==NULL){
        cout<<"\nData kosong\n";
        pause();
        return;
    }

    Barang b[100];
    int n=0;

    while(fscanf(fp,"%[^|]|%d|%d\n",b[n].nama,&b[n].harga,&b[n].stok)!=EOF){
        n++;
    }

    fclose(fp);

    char cari[50];
    
    cout<<"=== Edit barang ===\n";
    cout<<"Nama barang: ";
    cin.ignore();
    cin.getline(cari,50);

    bool found=false;

    for(int i=0;i<n;i++){

        if(bandingString(b[i].nama,cari)==0){

            cout<<"\nData ditemukan\n";

            cout<<"Nama : "<<b[i].nama<<endl;
            cout<<"Harga : "<<b[i].harga<<endl;
            cout<<"Stok : "<<b[i].stok<<endl;

            cout<<"\nMasukkan data baru\n";

            cout<<"Nama: ";
            cin.getline(b[i].nama,50);

            cout<<"Harga: ";
            cin>>b[i].harga;

            cout<<"Stok: ";
            cin>>b[i].stok;

            found=true;
        }
    }

    if(!found)
        cout<<"Data tidak ditemukan\n";

    fp=fopen("barang.txt","w");

    for(int i=0;i<n;i++){
        fprintf(fp,"%s|%d|%d\n",b[i].nama,b[i].harga,b[i].stok);
    }

    fclose(fp);
    success();
} 

void sequentialSearch(){

    FILE *fp=fopen("barang.txt","r");

    if(fp==NULL){
        cout<<"Data kosong\n";
        pause();
        return;
    }

    Barang b;
    char cari[50];
    
    cout<<"=== Sequential Search ===\n";
    cout<<"Nama barang: ";
    cin.ignore();
    cin.getline(cari,50);

    bool found=false;

    while(fscanf(fp,"%[^|]|%d|%d\n",b.nama,&b.harga,&b.stok)!=EOF){

        if(bandingString(b.nama,cari)==0){

            cout<<"\nData ditemukan!\n";
            cout<<"Nama : "<<b.nama<<endl;
            cout<<"Harga : "<<b.harga<<endl;
            cout<<"Stok : "<<b.stok<<endl;

            found=true;
        }
    }

    if(!found)
        cout<<"Data tidak ditemukan\n";

    fclose(fp);
    pause();
}

void binarySearch(){

    FILE *fp=fopen("barang.txt","r");

    if(fp==NULL){
        cout<<"Data kosong\n";
        pause();
        return;
    }

    Barang b[100];
    int n=0;

    while(fscanf(fp,"%[^|]|%d|%d\n",b[n].nama,&b[n].harga,&b[n].stok)!=EOF){
        n++;
    }

    fclose(fp);

    sortNama(b,n);

    char cari[50];
    
    cout<<"=== Binary Search ===\n";
    cout<<"Nama barang: ";
    cin.ignore();
    cin.getline(cari,50);

    int kiri=0;
    int kanan=n-1;
    bool found=false;

    while(kiri<=kanan){

        int mid=(kiri+kanan)/2;

        int hasil=bandingString(b[mid].nama,cari);

        if(hasil==0){

            cout<<"\nData ditemukan!\n";
            cout<<"Nama : "<<b[mid].nama<<endl;
            cout<<"Harga : "<<b[mid].harga<<endl;
            cout<<"Stok : "<<b[mid].stok<<endl;

            found=true;
            break;
        }

        else if(hasil<0)
            kiri=mid+1;
        else
            kanan=mid-1;
    }

    if(!found)
        cout<<"Data tidak ditemukan\n";

    pause();
}

void cariBarang(){

    int pilih;
    
    cout<<"=== Cari Barang ===\n";
    cout<<"1 Sequential Search\n";
    cout<<"2 Binary Search\n";
    cout<<"====================\n";
    cout<<"Pilih: ";
    cin>>pilih;
    system("cls");

    if(pilih==1)
        sequentialSearch();
    else
        binarySearch();
}

void menuAdmin(){

    int pilih;

    do{

        cout<<"\n=== Halo ADMIN! ===\n";
        cout<<"1 Tambah Karyawan\n";
        cout<<"2 Lihat Karyawan\n";
        cout<<"3 Cari Karyawan\n";
        cout<<"4 Logout\n";
        cout<<"======================\n";
        cout<<"Pilih: ";
        cin>>pilih;

        system("cls");

        switch(pilih){

            case 1: tambahKaryawan(); break;
            case 2: lihatKaryawan(); break;
            case 3: cariKaryawan(); break;
        }

    }while(pilih!=4);
}

void menuKaryawan(){

    int pilih;

    do{

        cout<<"\n=== Halo KARYAWAN! ===\n";
        cout<<"1 Tambah Barang\n";
        cout<<"2 Lihat Barang\n";
        cout<<"3 Edit Barang\n";
        cout<<"4 Cari Barang\n";
        cout<<"5 Logout\n";
        cout<<"========================\n";
        cout<<"Pilih: ";
        cin>>pilih;

        system("cls");

        switch(pilih){

            case 1: tambahBarang(); break;
            case 2: lihatBarang(); break;
            case 3: editBarang(); break;
            case 4: cariBarang(); break;
        }

    }while(pilih!=5);
}

int main(){

    int pilih;

    do{

        cout<<"\n===== WELCOME TO COCOA HEAVEN =====\n";
        cout<<"1 Login Admin\n";
        cout<<"2 Karyawan\n";
        cout<<"3 Keluar\n";
        cout<<"======================================\n";
        cout<<"Pilih: ";
        cin>>pilih;

        system("cls");

        if(pilih==1){

            char user[20];
            char pass[20];
            
            cout<<"=== Login Admin ===\n";
            cout<<"Username: ";
            cin>>user;

            cout<<"Password: ";
            cin>>pass;

            if(bandingString(user,"admin")==0 && bandingString(pass,"123")==0){

                system("cls");
                menuAdmin();
            }

            else{

                cout<<"Login gagal, bukan admin!\n";
                pause();
            }
        }

        if(pilih==2)
            menuKaryawan();

    }while(pilih!=3);

}
