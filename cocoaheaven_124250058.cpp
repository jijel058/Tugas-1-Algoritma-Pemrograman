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

int bandingString(char a[], char b[]){
    int i=0;
    while(a[i] != '\0' && b[i] != '\0'){
        if(a[i] != b[i]) return 1;
        i++;
    }
    if(a[i]=='\0' && b[i]=='\0')
        return 0;
    else
        return 1;
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

void tambahKaryawan(){

    FILE *fp=fopen("karyawan.txt","a");

    int n;
    cout<<"Jumlah karyawan: ";
    cin>>n;

    Karyawan k[n];
    Karyawan *ptr=k;

    for(int i=0;i<n;i++){

        cout<<"ID: ";
        cin>>(ptr+i)->id;

        cout<<"Nama: ";
        cin>>(ptr+i)->nama;

        fprintf(fp,"%d %s\n",(ptr+i)->id,(ptr+i)->nama);
    }

    fclose(fp);
}

void lihatKaryawan(){

    FILE *fp=fopen("karyawan.txt","r");

    Karyawan k;

    cout<<"\nData Karyawan\n";

    while(fscanf(fp,"%d %s",&k.id,k.nama)!=EOF){

        cout<<"ID : "<<k.id<<endl;
        cout<<"Nama : "<<k.nama<<endl;
        cout<<"----------------\n";
    }

    fclose(fp);
}

void cariKaryawan(){

    FILE *fp=fopen("karyawan.txt","r");

    int id;
    cout<<"Masukkan ID: ";
    cin>>id;

    Karyawan k;
    bool found=false;

    while(fscanf(fp,"%d %s",&k.id,k.nama)!=EOF){

        if(k.id==id){

            cout<<"Data ditemukan\n";
            cout<<"ID: "<<k.id<<endl;
            cout<<"Nama: "<<k.nama<<endl;
            found=true;
        }
    }

    if(!found)
    cout<<"Data tidak ditemukan\n";

    fclose(fp);
}

void tambahBarang(){

    FILE *fp=fopen("barang.txt","a");

    int n;
    cout<<"Jumlah barang: ";
    cin>>n;

    Barang b[n];
    Barang *ptr=b;

    for(int i=0;i<n;i++){

        cout<<"Nama: ";
        cin>>(ptr+i)->nama;

        cout<<"Harga: ";
        cin>>(ptr+i)->harga;

        cout<<"Stok: ";
        cin>>(ptr+i)->stok;

        fprintf(fp,"%s %d %d\n",(ptr+i)->nama,(ptr+i)->harga,(ptr+i)->stok);
    }

    fclose(fp);
}

void lihatBarang(){

    FILE *fp=fopen("barang.txt","r");

    Barang b[100];
    int n=0;

    while(fscanf(fp,"%s %d %d",b[n].nama,&b[n].harga,&b[n].stok)!=EOF){
        n++;
    }

    fclose(fp);

    int pilih;

    cout<<"1 Ascending\n";
    cout<<"2 Descending\n";
    cin>>pilih;

    if(pilih==1)
        bubbleSort(b,n);
    else
        quickSort(b,0,n-1);

    for(int i=0;i<n;i++){

        cout<<"Nama : "<<b[i].nama<<endl;
        cout<<"Harga : "<<b[i].harga<<endl;
        cout<<"Stok : "<<b[i].stok<<endl;
        cout<<"----------------\n";
    }
}

void editBarang(){

    FILE *fp=fopen("barang.txt","r");

    Barang b[100];
    int n=0;

    while(fscanf(fp,"%s %d %d",b[n].nama,&b[n].harga,&b[n].stok)!=EOF){
        n++;
    }

    fclose(fp);

    char cari[50];
    cout<<"Nama barang: ";
    cin>>cari;

    for(int i=0;i<n;i++){

        if(bandingString(b[i].nama,cari)==0){

            cout<<"Data lama\n";
            cout<<b[i].nama<<" "<<b[i].harga<<" "<<b[i].stok<<endl;

            cout<<"Nama baru: ";
            cin>>b[i].nama;

            cout<<"Harga baru: ";
            cin>>b[i].harga;

            cout<<"Stok baru: ";
            cin>>b[i].stok;
        }
    }

    fp=fopen("barang.txt","w");

    for(int i=0;i<n;i++){
        fprintf(fp,"%s %d %d\n",b[i].nama,b[i].harga,b[i].stok);
    }

    fclose(fp);
}

void sequentialSearch(){

    FILE *fp=fopen("barang.txt","r");

    Barang b;
    char cari[50];

    cout<<"Nama barang: ";
    cin>>cari;

    bool found=false;

    while(fscanf(fp,"%s %d %d",b.nama,&b.harga,&b.stok)!=EOF){

        if(bandingString(b.nama,cari)==0){

            cout<<"Ditemukan\n";
            cout<<b.nama<<" "<<b.harga<<" "<<b.stok<<endl;

            found=true;
        }
    }

    if(!found)
    cout<<"Tidak ditemukan\n";

    fclose(fp);
}

void menuAdmin(){

    int pilih;

    do{

        cout<<"\n Admin\n";
        cout<<"1 Tambah Karyawan\n";
        cout<<"2 Lihat Karyawan\n";
        cout<<"3 Cari Karyawan\n";
        cout<<"4 Logout\n";
        cin>>pilih;

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

        cout<<"\nMenu Karyawan\n";
        cout<<"1 Tambah Barang\n";
        cout<<"2 Lihat Barang\n";
        cout<<"3 Edit Barang\n";
        cout<<"4 Cari Barang (Sequential)\n";
        cout<<"5 Logout\n";

        cin>>pilih;

        switch(pilih){

            case 1: tambahBarang(); break;
            case 2: lihatBarang(); break;
            case 3: editBarang(); break;
            case 4: sequentialSearch(); break;
        }

    }while(pilih!=5);
}

int main(){

    int pilih;

    do{

        cout<<"\n====== WELCOME TO COCOA HEAVEN ======\n";
        cout<<"1 Login Admin\n";
        cout<<"2 Karyawan\n";
        cout<<"3 Keluar\n";
        cout<<"\n=======================================\n";
		cout<<"Masukkan Pilihan Menu: ";
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

                menuAdmin();
            }
            else{

                cout<<"Bukan Admin!\n";
            }
        }

        if(pilih==2)
        menuKaryawan();

    }while(pilih!=3);

}
