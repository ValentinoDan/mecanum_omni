# Inverse Kinematics: Mecanum & Omni Wheel

Package ROS 2 ini adalah ditujukan untuk memahami **Inverse Kinematics** pada robot roda Mecanum dan Omni, hanya perlu melengkapi **2 file** agar semua test berhasil (PASS).

---

## Alur Tugas & Pengumpulan

1. Fork repository
2. Lengkapi kode
3. Tampilkan screenshot program berhasil pada README
4. Lakukan Pull Request

---

## Derajat Kebebasan Robot

Robot holonomic memiliki 3 derajat kebebasan: maju/mundur (`vx`), geser kiri/kanan (`vy`), dan rotasi (`omega`).

---

## Perbedaan Mecanum vs Omni Wheel

Kedua roda ini membuat robot bisa bergerak ke **semua arah** (holonomic), tapi caranya berbeda:

### Mecanum Wheel
- Roda utamanya menghadap ke depan/belakang (*seperti roda biasa*)
- Di sekelling rodanya ada **roller kecil miring 45°**
- Roller inilah yang memungkinkan robot **geser menyamping (strafe)** saat roda berputar berlawanan arah
- Contoh penggunaan: robot forklift
- **Keunggulan**: daya dorong besar ke depan, tetap bisa geser
- **Cara kerja**: kombinasi putaran 4 roda menghasilkan gerak maju, geser, atau putar

### Omni Wheel
- Roda utamanya juga menghadap ke depan, tapi roller-nya **tegak lurus (90°)** terhadap arah putaran roda
- Roller 90° ini membuat roda bisa **bergerak bebas ke samping** tanpa hambatan
- Biasanya dipasang dalam **konfigurasi X** (4 roda di sudut-sudut robot, masing-masing menghadap sudut tertentu)
- Contoh penggunaan: robot sepak bola, robot pengantar barang
- **Keunggulan**: mekanisme lebih sederhana, geser sangat lancar
- **Cara kerja**: tiap roda didorong sesuai komponen arahnya, lalu jumlahkan

---

### Perbandingan Singkat

| Aspek | Mecanum | Omni |
|---|---|---|
| Sudut roller | 45° | 90° |
| Arah roller | Miring | Tegak lurus roda |
| Konfigurasi roda | 4 roda, 2 kiri & 2 kanan | 4 roda di sudut (X-config) |
| Gaya dorong ke depan | Kuat | Sedang |
| Geser menyamping | Bisa, tapi sedikit kalah kuat | Sangat lancar |


> **Intinya**: Mecanum cocok kalau butuh **daya dorong besar + geser**. Omni cocok kalau butuh **geser sangat lancar + mekanisme sederhana**

---

## Setup Workspace

Jika belum punya workspace ROS 2, buat dulu:

```bash
# 1. Buat folder workspace dan src
mkdir -p ~/nama_workspace/src

# 2. Clone repo ini ke dalam src
cd ~/nama_workspace/src
git clone https://github.com/ValentinoDan/mecanum_omni.git

# 3. Build workspace (*abaikan warning*)
cd ~/nama_workspace
source install/setup.bash
colcon build --packages-select mecanum_omni
```

---

## File yang Harus Dikerjakan

Hanya **2 file** ini yang perlu diisi:

| File | Deskripsi |
|---|---|
| `src/mecanum.cpp` | Implementasi rumus Inverse Kinematics Mecanum |
| `src/omni.cpp` | Implementasi rumus Inverse Kinematics Omni |

**File lain sudah siap dipakai**, tidak perlu diubah

---

## Petunjuk Mengerjakan

### 1. Lihat Rumus di Header

Buka file header untuk melihat rumus matematika lengkap:
- `include/mecanum_omni/mecanum.hpp` — rumus dan penjelasan Mecanum
- `include/mecanum_omni/omni.hpp` — rumus dan penjelasan Omni

Semua rumus sudah disediakan, tinggal diimplementasikan

### 2. Isi File `src/mecanum.cpp`

Cari baris `// TODO:` dan isi dengan rumus dari header. Contoh awalnya sudah ada di komentar

### 3. Isi File `src/omni.cpp`

Sama seperti di atas, cari `// TODO:` dan implementasikan rumus Omni

### 4. Build & Test

Setiap kali mengubah kode, jalankan perintah berikut di terminal:

```bash
# Masuk ke workspace
cd ~/<workspace>

# Build package
colcon build --packages-select mecanum_omni

# Jalankan test
colcon test --packages-select mecanum_omni

# Lihat hasil test detail
colcon test-result --verbose
```

---

## Hasil yang Diharapkan

| Kondisi | Test |
|---|---|
| **Sebelum mengerjakan** (`TODO` masih kosong) | Test **FAIL**|
| **Setelah mengerjakan** (rumus benar) | Test **PASS**|

Kalau masih **FAIL**, cek log test untuk melihat nilai yang salah. Bandingkan dengan expected value yang tercantum.

---

## Menjalankan Demo Node

Setelah test PASS, bisa coba jalanin demo untuk melihat hasilnya:

```bash
# Terminal 1 — jalankan node
source install/setup.bash
ros2 launch mecanum_omni demo.launch.py

# Terminal 2 — kirim perintah gerak
source install/setup.bash
ros2 topic pub /cmd_vel geometry_msgs/msg/Twist "{linear: {x: 1.0, y: 0.0}, angular: {z: 0.0}}"
```

Node akan subscribe `/cmd_vel` dan publish kecepatan roda ke topic `/wheel_speeds`

---

## Ganti Solver (Mecanum ↔ Omni)

Secara default demo pakai solver **mecanum**. Untuk pakai **omni**:

```bash
ros2 launch mecanum_omni demo.launch.py solver_type:=omni
```