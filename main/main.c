#include "./includeADT.h"

int main()
{

    // Utilities
    boolean login = false;
    boolean runProgram = true;

    // Array untuk menampung user saat ini
    AccountList akun;
    CreateAccountList(&akun);
    Graf teman;
    createEmptyGraf(&teman);
    prioqueuefren Q;
    MakeEmptyprio(&Q, 100);
    Stack draf;
    CreateEmptyStack(&draf);
    ReadUser_FILE("../cfg/pengguna.config", &akun, &teman, &Q);
    ReadDraf_FILE("../cfg/draf.config", &akun, &draf);

    Stack drafStack[20]; // Buat 20 stack untuk 20 pengguna
    // int userID = 0;                  // ID pengguna saat ini
    // CreateEmpty(&drafStack[userID]); // Inisialisasi stack untuk pengguna saat ini
    int i;
    for (i = 0; i < 20; i++)
    {
        CreateEmptyStack(&drafStack[i]);
    }

    while (!IsEmptyStack(draf))
    {
        drafkicau temp;
        Pop(&draf, &temp);
        for (i = 0; i < 20; i++)
        {
            if (temp.IDuser == i)
            {
                Push(&drafStack[i], temp);
            }
        }
    }

    Account akunLogin;
    ListKicau kList;
    CreateListKicau(&kList);
    Kicau k;
    ReadKicau_FILE("../cfg/kicauan.config", &kList);
    int idUtas = 0;
    readUtas("../cfg/utas.config",&kList,&idUtas,akun);

    boolean isLogin = false;
    printf("           ____  __  __  ____  ____  ____  ____ /\\ \n");
    printf("    __    (  _ \\(  )(  )(  _ \\(  _ \\(_  _)(  _ \\)(    __    \n");
    printf("___( o)>   ) _ < )(__)(  )   / ) _ < _)(_  )   /\\/  <(o )___\n");
    printf("\\ <_. )   (____/(______)(_)\\_)(____/(____)(_)\\_)()   ( ._> /\n");
    printf(" `---'              Tempat Anda Mencibir              `---' \n\n");

    printf("Selamat datang di Burbir. Selamat berkicau!\n");
    while (runProgram)
    {
        printf(">> ");
        STARTCOMMAND();

        Word command = currentWord;
        Word tutup_program = {"TUTUP_PROGRAM", 13};
        Word daftar = {"DAFTAR", 6};
        Word masuk = {"MASUK", 5};
        Word keluar = {"KELUAR", 6};
        Word ganti_profil = {"GANTI_PROFIL", 12};
        Word jenis_akun = {"ATUR_JENIS_AKUN", 15};
        Word ubah_foto = {"UBAH_FOTO_PROFIL", 16};
        Word lihat_profil = {"LIHAT_PROFIL", 12};
        Word curr_user = {"USER", 4};
        Word daftar_teman = {"DAFTAR_TEMAN", 12};
        Word hapus_teman = {"HAPUS_TEMAN", 11};
        Word tambah_teman = {"TAMBAH_TEMAN", 12};
        Word daftar_permintaan_teman = {"DAFTAR_PERMINTAAN_PERTEMANAN", 28};
        Word setujui_pertemanan = {"SETUJUI_PERTEMANAN", 18};
        Word utas = {"UTAS", 4};
        Word kicau = {"KICAU", 5};
        Word suka_kicauan = {"SUKA_KICAUAN", 10};
        Word kicauan = {"KICAUAN", 7};
        Word cari_kicauan = {"CARI_KICAUAN", 12};
        Word ubah_kicauan = {"UBAH_KICAUAN", 12};
        Word balas = {"BALAS", 5};
        Word sambung_utas = {"SAMBUNG_UTAS", 12};
        Word hapus_utas = {"HAPUS_UTAS", 10};
        Word cetak_utas = {"CETAK_UTAS", 10};
        Word buat_draf = {"BUAT_DRAF", 9};
        Word lihat_draf = {"LIHAT_DRAF", 10};

        if (WordEqual(command, tutup_program))
        {
            SaveUser_FILE("../cfg/pengguna.config", &akun, teman, Q);
            SaveDraf_FILE("../cfg/draf.config", &akun, drafStack);
            saveKicau_FILE("../cfg/kicauan.config", kList);
            saveUtas("../cfg/utas.config",&kList,idUtas,akun);
            runProgram = false;
        }
        else if (WordEqual(command, daftar))
        {
            if (isLogin)
            {
                printf("Anda sedang login dengan akun %s, silahkan keluar dulu.\n", akunLogin.username->TabWord);
            }
            else if (IsAccountListFull(&akun))
            {
                printf("Batas jumlah pengguna sudah tercapai, tidak dapat menambahkan akun baru.\n");
            }
            else
            {
                signup(&akun);
                teman.mem[akun.count-1][akun.count-1] = 1;
            }
        }

        else if (WordEqual(command, masuk))
        {
            if (isLogin)
            {
                printf("Anda sudah login dengan akun %s\n", akunLogin.username->TabWord);
            }
            else
            {
                signin(&akun, &akunLogin);
                isLogin = true;
            }
        }

        else if (WordEqual(command, ganti_profil))
        {
            if (!isLogin)
            {
                printf("Anda belum masuk! Masuk terlebih dahulu untuk menikmati layanan BurBir.\n");
            }
            else
            {
                edit_profile(&akun, akunLogin);
            }
        }

        else if (WordEqual(command, keluar))
        {
            if (!isLogin)
            {
                printf("Anda belum masuk! Masuk terlebih dahulu untuk menikmati layanan BurBir.\n");
            }
            else
            {
                printf("Keluar dari akun dengan username %s\n", akunLogin.username->TabWord);
                outUser(&akunLogin);
                isLogin = false;
            }
        }

        else if (WordEqual(command, jenis_akun))
        {
            if (!isLogin)
            {
                printf("Anda belum masuk! Masuk terlebih dahulu untuk menikmati layanan BurBir.\n");
            }
            else
            {
                ganti_jenis_akun(&akun, akunLogin);
            }
        }

        else if (WordEqual(command, ubah_foto))
        {
            if (!isLogin)
            {
                printf("Anda belum masuk! Masuk terlebih dahulu untuk menikmati layanan BurBir.\n");
            }
            else
            {
                edit_foto(&akun, akunLogin);
            }
        }

        else if (WordEqual(command, curr_user))
        {
            DisplayAccounts(&akun);
        }
        else if (WordEqual(command, hapus_teman))
        {
            hapusteman(isLogin, akunLogin, &akun, &teman);
        }
        else if (WordEqual(command, tambah_teman))
        {
            tambahteman(isLogin, akunLogin, &akun, teman, &Q);
        }
        else if (WordEqual(command, daftar_permintaan_teman))
        {
            daftarpermintaanteman(isLogin, akunLogin, &akun, &Q);
        }
        else if (WordEqual(command, setujui_pertemanan))
        {
            setujuipermintaanteman(isLogin, akunLogin, &akun, &teman, &Q);
        }
        else if (wordCheck(command, 0, 11, lihat_profil) && command.Length > 12)
        {
            if (!isLogin)
            {
                printf("Anda belum masuk! Masuk terlebih dahulu untuk menikmati layanan BurBir.\n");
            }
            else
            {
                show_profile(&akun, wordFromIndex(command, 13));
            }
        }
        else if (wordCheck(command, 0, 3, utas)) // utas
        {
            int i = 5;
            int id = 0;
            while (i < command.Length)
            {
                id *= 10;
                id += CharToInt(command.TabWord[i]);
                i++;
            }
            createUtas(id, &kList, akunLogin, &idUtas);
        }
        else if (wordCheck(command, 0, 11, sambung_utas)) // sambung utas
        {
            int idUtas = 0;
            int index = 0;
            int i = 13;
            while (command.TabWord[i] != ' ')
            {
                idUtas *= 10;
                idUtas += CharToInt(command.TabWord[i]);
                i++;
            }
            i++;
            while (i<command.Length)
            {
                index *= 10;
                index += CharToInt(command.TabWord[i]);
                i++;
            }
            sambungUtas(idUtas, index, &kList, akunLogin);
        }
        else if (wordCheck(command, 0, 9, hapus_utas)) // hapus utas
        {
            int idUtas = 0;
            int index = 0;
            int i = 11;
            while (command.TabWord[i] != ' ')
            {
                idUtas *= 10;
                idUtas += CharToInt(command.TabWord[i]);
                i++;
            }
            i++;
            while (i<command.Length)
            {
                index *= 10;
                index += CharToInt(command.TabWord[i]);
                i++;
            }
            hapusUtas(idUtas, index, &kList, akunLogin);
        }
        else if (wordCheck(command, 0, 9, cetak_utas)) // cetak utas
        {
            int idUtas = 0;
            int i = 11;
            while (i<command.Length)
            {
                idUtas *= 10;
                idUtas += CharToInt(command.TabWord[i]);
                i++;
            }
            cetakUtas(idUtas, kList, akunLogin, &akun, teman);
        }
        else if (WordEqual(command, buat_draf))
        {
            int idUser;
            i = 0;
            boolean found = false;
            while (i < akun.count && found == false)
            {
                if (WordEqual(*akun.accounts[i].username, *akunLogin.username))
                {
                    idUser = i;
                    found = true;
                }
                i++;
            }
            if (isLogin)
            {
                drafkicau DrafUser;
                STARTSENTENCE();
                printf("Masukkan draf:\n");

                // Akuisisi dan simpan draf dalam stack
                STARTSENTENCE();
                CopyWordTo(&DrafUser.Draf, currentWord);
                time_t rawtime;
                struct tm *timeinfo;

                time(&rawtime);                 // Get the current time
                timeinfo = localtime(&rawtime); // Convert to local time

                // Access individual components
                int SS, M, HH, DD, MM, YY;
                getlocaltime(&SS, &M, &HH, &DD, &MM, &YY);
                DATETIME waktudraf;
                CreateDATETIME(&waktudraf, DD, MM, YY, HH, M, SS);
                DrafUser.waktu = waktudraf;
                DrafUser.IDuser = idUser;
                Push(&drafStack[idUser], DrafUser);

                printf("Apakah anda ingin menghapus, menyimpan, atau menerbitkan draf ini?\n");
                ADVSENTENCE();

                while (1)
                {
                    STARTWORD();
                    if (WordEqual(currentWord, stringToWord("HAPUS", 5)))
                    {
                    // Pengguna ingin menghapus draf
                    if (!IsEmptyStack(drafStack[idUser]))
                    {
                        Pop(&drafStack[idUser], &DrafUser);
                        printf("Draf telah berhasil dihapus!\n");
                    }
                    else
                    {
                        printf("Tidak ada draf yang bisa dihapus.\n");
                    }
                    break;
                    }
                    else if (WordEqual(currentWord, stringToWord("SIMPAN", 6)))
                    {
                    // Pengguna ingin menyimpan draf
                    printf("Draf telah berhasil disimpan!\n");
                    break;
                    }
                    else if (WordEqual(currentWord, stringToWord("TERBIT", 6)))
                    {
                    // Pengguna ingin menerbitkan draf
                    Pop(&drafStack[idUser], &DrafUser);
                    DATETIME waktuterbit;
                    int SS, M, HH, DD, MM, YY;
                    getlocaltime(&SS, &M, &HH, &DD, &MM, &YY);
                    CreateDATETIME(&waktuterbit, DD, MM, YY, HH, M, SS);
                    DrafUser.waktu = waktuterbit;

                    ADVWORD();

                    printf("Selamat! Draf kicauan telah diterbitkan!\n\n");
                    Kicau temp;
                    temp.id = kList.nEff + 1;
                    temp.like = 0;
                    wordToString(temp.text, DrafUser.Draf);
                    temp.author = *akun.accounts[idUser].username;
                    temp.datetime = waktuterbit;
                    temp.utasKicau = NULL;

                    // Tambahkan logikanya untuk menerbitkan draf
                    AddToKicauan(&kList, temp);

                    printf("Detil kicauan:\n");
                    printf("| ID = %d\n", temp.id);
                    printf("| ");
                    printWord(*akun.accounts[idUser].username);
                    printf("\n");
                    printf("| ");
                    TulisDATETIME(waktuterbit);
                    printf("\n");
                    printf("| ");
                    printWord(DrafUser.Draf);
                    printf("\n");
                    printf("| ");
                    printf("Disukai: 0\n");
                    break;
                    }
                    else
                    {
                    printf("Perintah tidak valid. Silakan masukkan 'HAPUS', 'SIMPAN', 'TERBIT', atau 'KEMBALI'.\n");
                    }
                }
            }
            else
            {
                printf("Anda belum masuk! Masuk terlebih dahulu untuk menikmati layanan BurBir.\n");
            }
        }
        else if (WordEqual(command, lihat_draf))
        {
            int idUser;
            i = 0;
            boolean found = false;
            while (i < akun.count && found == false)
            {
                if (WordEqual(*akun.accounts[i].username, *akunLogin.username))
                {
                    idUser = i;
                    found = true;
                }
                i++;
            }
            if (isLogin)
            {
                drafkicau DrafUser;

                // Check if the user has any drafts
                if (!IsEmptyStack(drafStack[idUser]))
                {
                    printf("Ini draf terakhir anda:\n");
                    printf("| ");
                    TulisDATETIME(InfoTop(drafStack[idUser]).waktu);
                    printf("\n");
                    printf("| ");
                    printWord(InfoTop(drafStack[idUser]).Draf);
                    printf("\n");

                    printf("\nApakah anda ingin mengubah, menghapus, atau menerbitkan draf ini? (KEMBALI jika ingin kembali)\n");

                    while (1)
                    {
                    STARTWORD();
                    if (WordEqual(currentWord, stringToWord("HAPUS", 5)))
                    {
                        // Pengguna ingin menghapus draf
                        if (!IsEmptyStack(drafStack[idUser]))
                        {
                        Pop(&drafStack[idUser], &DrafUser);
                        printf("Draf telah berhasil dihapus!\n");
                        }
                        else
                        {
                        printf("Tidak ada draf yang bisa dihapus.\n");
                        }
                        break;
                    }
                    else if (WordEqual(currentWord, stringToWord("UBAH", 4)))
                    {
                        // Akuisisi dan simpan draf baru dalam stack
                        Pop(&drafStack[idUser], &DrafUser);
                        STARTSENTENCE();
                        printf("Masukkan draf yang baru:\n");

                        // Akuisisi dan simpan draf dalam stack
                        STARTSENTENCE();
                        CopyWordTo(&DrafUser.Draf, currentWord);
                        time_t rawtime;
                        struct tm *timeinfo;
                        time(&rawtime);                 // Get the current time
                        timeinfo = localtime(&rawtime); // Convert to local time

                        // Access individual components
                        int SS, M, HH, DD, MM, YY;
                        getlocaltime(&SS, &M, &HH, &DD, &MM, &YY);
                        DATETIME waktudraf;
                        CreateDATETIME(&waktudraf, DD, MM, YY, HH, M, SS);
                        DrafUser.waktu = waktudraf;
                        Push(&drafStack[idUser], DrafUser);

                        printf("Apakah anda ingin menghapus, menyimpan, atau menerbitkan draf ini?\n");

                        while (1)
                        {
                        STARTWORD();
                        if (WordEqual(currentWord, stringToWord("HAPUS", 5)))
                        {
                            // Pengguna ingin menghapus draf
                            if (!IsEmptyStack(drafStack[idUser]))
                            {
                            Pop(&drafStack[idUser], &DrafUser);
                            printf("Draf telah berhasil dihapus!\n");
                            }
                            else
                            {
                            printf("Tidak ada draf yang bisa dihapus.\n");
                            }
                            break;
                        }
                        else if (WordEqual(currentWord, stringToWord("SIMPAN", 6)))
                        {
                            // Pengguna ingin menyimpan draf
                            printf("Draf telah berhasil disimpan!\n");
                            break;
                        }
                        else if (WordEqual(currentWord, stringToWord("TERBIT", 6)))
                        {
                            // Di-pop karena draf telah diterbitkan
                            Pop(&drafStack[idUser], &DrafUser);
                            DATETIME waktuterbit;
                            int SS, M, HH, DD, MM, YY;
                            getlocaltime(&SS, &M, &HH, &DD, &MM, &YY);
                            CreateDATETIME(&waktuterbit, DD, MM, YY, HH, M, SS);
                            DrafUser.waktu = waktuterbit;

                            ADVWORD();

                            printf("Selamat! Draf kicauan telah diterbitkan!\n\n");
                            Kicau temp;
                            temp.id = kList.nEff + 1;
                            temp.like = 0;
                            wordToString(temp.text, DrafUser.Draf);
                            temp.author = *akun.accounts[idUser].username;
                            temp.datetime = waktuterbit;
                            temp.utasKicau = NULL;

                            // Tambahkan logikanya untuk menerbitkan draf
                            AddToKicauan(&kList, temp);

                            printf("Detil kicauan:\n");
                            printf("| ID = %d\n", temp.id);
                            printf("| ");
                            printWord(*akun.accounts[idUser].username);
                            printf("\n");
                            printf("| ");
                            TulisDATETIME(waktuterbit);
                            printf("\n");
                            printf("| ");
                            printWord(DrafUser.Draf);
                            printf("\n");
                            printf("| ");
                            printf("Disukai: 0\n");
                            break;
                        }
                        else if (WordEqual(currentWord, stringToWord("KEMBALI", 7)))
                        {
                            // Pengguna ingin kembali
                            printf("Kembali ke draf sebelumnya.\n");
                            break;
                        }
                        else
                        {
                            printf("Perintah tidak valid. Silakan masukkan 'HAPUS', 'SIMPAN', 'TERBIT', atau 'KEMBALI'.\n");
                        }
                        }
                        break;
                    }
                    else if (WordEqual(currentWord, stringToWord("TERBIT", 6)))
                    {
                        // Di-pop karena draf telah diterbitkan
                        Pop(&drafStack[idUser], &DrafUser);
                        DATETIME waktuterbit;
                        int SS, M, HH, DD, MM, YY;
                        getlocaltime(&SS, &M, &HH, &DD, &MM, &YY);
                        CreateDATETIME(&waktuterbit, DD, MM, YY, HH, M, SS);
                        DrafUser.waktu = waktuterbit;

                        ADVWORD();

                        printf("Selamat! Draf kicauan telah diterbitkan!\n\n");
                        Kicau temp;
                        temp.id = kList.nEff + 1;
                        temp.like = 0;
                        wordToString(temp.text, DrafUser.Draf);
                        temp.author = *akun.accounts[idUser].username;
                        temp.datetime = waktuterbit;
                        temp.utasKicau = NULL;

                        // Tambahkan logikanya untuk menerbitkan draf
                        AddToKicauan(&kList, temp);

                        printf("Detil kicauan:\n");
                        printf("| ID = %d\n", temp.id);
                        printf("| ");
                        printWord(*akun.accounts[idUser].username);
                        printf("\n");
                        printf("| ");
                        TulisDATETIME(waktuterbit);
                        printf("\n");
                        printf("| ");
                        printWord(DrafUser.Draf);
                        printf("\n");
                        printf("| ");
                        printf("Disukai: 0\n");
                        break;
                    }
                    else if (WordEqual(currentWord, stringToWord("KEMBALI", 7)))
                    {
                        // Pengguna ingin kembali
                        printf("Kembali ke draf sebelumnya.\n");
                        break;
                    }
                    else
                    {
                        printf("Perintah tidak valid. Silakan masukkan 'HAPUS', 'UBAH', 'TERBIT', atau 'KEMBALI'.\n");
                    }
                    }
                }
                else
                {
                    printf("Yah, anda belum memiliki draf apapun! Buat dulu ya :D\n");
                }
            }
            else
            {
                printf("Anda belum masuk! Masuk terlebih dahulu untuk menikmati layanan BurBir.\n");
            }
        }
         else if (WordEqual(command, kicau))
        {
            if (isLogin)
            {
                CreateKicau(akunLogin, &kList, &k);
            }
            else
            {
                printf("Anda belum masuk! Masuk terlebih dahulu untuk menikmati layanan BurBir.\n");
            }
        }
        else if (wordCheck(command, 0, 9, suka_kicauan) && command.Length > 10)
        {
            if (isLogin)
            {
                SukaKicau(akunLogin, wordFromIndex(command, 11), &kList, &k, &akun, teman);
            }
            else
            {
                printf("Anda belum masuk! Masuk terlebih dahulu untuk menikmati layanan BurBir.\n");
            }
        }
        else if (WordEqual(command, kicauan))
        {
            if (isLogin)
            {
                Kicauan(akunLogin, kList);
            }
            else
            {
                printf("Anda belum masuk! Masuk terlebih dahulu untuk menikmati layanan BurBir.\n");
            }
        }
        else if (wordCheck(command, 0, 11, ubah_kicauan) && command.Length > 12)
        {
            if (isLogin)
            {
                UbahKicau(akunLogin, wordFromIndex(command, 13), &kList);
            }
            else
            {
                printf("Anda belum masuk! Masuk terlebih dahulu untuk menikmati layanan BurBir.\n");
            }
        }
        else if (wordCheck(command, 0, 11, cari_kicauan) && command.Length > 12)
        {
            printf("Masuk\n");
            if (isLogin)
            {
                KicauanTagar(kList, wordFromIndex(command, 13));
            }
            else
            {
                printf("Anda belum masuk! Masuk terlebih dahulu untuk menikmati layanan BurBir.\n");
            }
        }
        else
        {
            printf("Perintah tidak dikenali.\n");
        }
    }
    ADVCOMMAND();
    return 0;
}
