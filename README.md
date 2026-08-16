# Praktikum Inverse Kinematics — Mecanum & Omni Wheel

Package ROS 2 ini adalah template praktikum untuk memahami **Inverse Kinematics** pada robot roda Mecanum dan Omni. Kamu hanya perlu melengkapi **2 file** agar semua test berhasil (PASS).

---

## Apa yang Kamu Pelajari?

Robot holonomic memiliki 3 derajat kebebasan: maju/mundur (`vx`), geser kiri/kanan (`vy`), dan rotasi (`omega`). Tugas kamu adalah menghitung kecepatan sudut tiap roda (`rad/s`) dari kecepatan body robot.

- **Mecanum**: 4 roda dengan roller 45°.
- **Omni**: 4 roda dengan roller 90° (konfigurasi X).

---

## Perbedaan Mecanum vs Omni Wheel

Kedua roda ini membuat robot bisa bergerak ke **semua arah** (holonomic), tapi caranya berbeda:

### Mecanum Wheel
- Roda utamanya menghadap ke depan/belakang (seperti roda biasa).
- Di sekelling rodanya ada **roller kecil miring 45°**.
- Roller inilah yang memungkinkan robot **geser menyamping (strafe)** saat roda berputar berlawanan arah.
- Contoh penggunaan: robot forklift, robot kompetisi FRC.
- **Keunggulan**: daya dorong besar ke depan, tetap bisa geser.
- **Cara kerja**: kombinasi putaran 4 roda menghasilkan gerak maju, geser, atau putar.

### Omni Wheel
- Roda utamanya juga menghadap ke depan, tapi roller-nya **tegak lurus (90°)** terhadap arah putaran roda.
- Roller 90° ini membuat roda bisa **bergerak bebas ke samping** tanpa hambatan.
- Biasanya dipasang dalam **konfigurasi X** (4 roda di sudut-sudut robot, masing-masing menghadap sudut tertentu).
- Contoh penggunaan: robot sepak bola, robot pengantar barang.
- **Keunggulan**: mekanisme lebih sederhana, geser sangat lancar.
- **Cara kerja**: tiap roda didorong sesuai komponen arahnya, lalu jumlahkan.

### Perbandingan Singkat

| Aspek | Mecanum | Omni |
|---|---|---|
| Sudut roller | 45° | 90° |
| Arah roller | Miring | Tegak lurus roda |
| Konfigurasi roda | 4 roda, 2 kiri & 2 kanan | 4 roda di sudut (X-config) |
| Gaya dorong ke depan | Kuat | Sedang |
| Geser menyamping | Bisa, tapi sedikit kalah kuat | Sangat lancar |
| Kompleksitas rumus | Perlu matrix 4×3 | Perlu proyeksi ke tiap arah roda |

> **Intinya**: Mecanum cocok kalau butuh **daya dorong besar + geser**. Omni cocok kalau butuh **geser sangat lancar + mekanisme sederhana**.

---

## Persiapan Awal (Setup Workspace)

Jika belum punya workspace ROS 2, buat dulu:

```bash
# 1. Buat folder workspace dan src
mkdir -p ~/nama_workspace/src

# 2. Clone repo ini ke dalam src
# (tanya asisten/dosen untuk URL repo)
cd ~/nama_workspace/src
git clone <URL_REPO_GITHUB> mecanum_omni

# 3. Build workspace
cd ~/nama_workspace
source ~/ros2_humble/install/local_setup.bash
colcon build --packages-select mecanum_omni
```

> **Catatan**: Folder `build/`, `install/`, dan `log/` akan muncul di **root workspace** (satu level di atas `src/`), bukan di dalam package. Ini standar ROS 2 — jangan khawatir.

---

## File yang Harus Dikerjakan

Hanya **2 file** ini yang perlu diisi:

| File | Deskripsi |
|---|---|
| `src/mecanum.cpp` | Implementasi rumus Inverse Kinematics Mecanum |
| `src/omni.cpp` | Implementasi rumus Inverse Kinematics Omni |

**File lain sudah siap pakai**, tidak perlu diubah.

---

## Petunjuk Mengerjakan

### 1. Lihat Rumus di Header

Buka file header untuk melihat rumus matematika lengkap:
- `include/mecanum_omni/mecanum.hpp` — rumus dan penjelasan Mecanum
- `include/mecanum_omni/omni.hpp` — rumus dan penjelasan Omni

Semua rumus sudah tertulis di sana, tinggal diterjemahkan ke C++.

### 2. Isi File `src/mecanum.cpp`

Cari baris `// TODO:` dan isi dengan rumus dari header. Contoh awalnya sudah ada di komentar.

### 3. Isi File `src/omni.cpp`

Sama seperti di atas, cari `// TODO:` dan implementasikan rumus Omni.

### 4. Build & Test

Setiap kali mengubah kode, jalankan perintah berikut di terminal:

```bash
# Masuk ke workspace
cd ~/krai/pengganti_day_2_ws

# Source ROS 2 (wajib di tiap terminal baru)
source ~/ros2_humble/install/local_setup.bash

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
| **Sebelum mengisi** (`TODO` masih kosong) | Test **FAIL** (merah) ✅ wajar |
| **Setelah mengisi** (rumus benar) | Test **PASS** (hijau) ✅ berhasil |

Kalau masih **FAIL**, cek log test untuk melihat nilai yang salah. Bandingkan dengan expected value yang tercantum.

---

## Menjalankan Demo Node

Setelah test PASS, kamu bisa menjalankan demo untuk melihat hasil secara real-time:

```bash
# Terminal 1 — jalankan node
source ~/ros2_humble/install/local_setup.bash
ros2 launch mecanum_omni demo.launch.py

# Terminal 2 — kirim perintah gerak
source ~/ros2_humble/install/local_setup.bash
ros2 topic pub /cmd_vel geometry_msgs/msg/Twist "{linear: {x: 1.0, y: 0.0}, angular: {z: 0.0}}"
```

Node akan subscribe `/cmd_vel` dan publish kecepatan roda ke topic `/wheel_speeds`.

---

## Ganti Solver (Mecanum ↔ Omni)

Secara default demo pakai solver **mecanum**. Untuk pakai **omni**:

```bash
ros2 launch mecanum_omni demo.launch.py solver_type:=omni
```

---

## Butuh Bantuan? Lihat Jawaban

Kalau buntu, jawaban lengkap tersedia di folder `answers/`:
- `answers/mecanum.cpp`
- `answers/omni.cpp`

**Cara pakai jawaban** (untuk belajar, bukan untuk disalin langsung tanpa paham):
1. Baca dan pahami kode di `answers/`
2. Bandingkan dengan skeleton di `src/`
3. Implementasikan sendiri di `src/` berdasarkan pemahamanmu.

---

## Daftar File & Struktur

```
mecanum_omni/
├── src/
│   ├── mecanum.cpp          ← TODO: isi rumus Mecanum
│   ├── omni.cpp             ← TODO: isi rumus Omni
│   └── main.cpp             ← Node ROS (sudah jadi, jangan ubah)
├── include/mecanum_omni/
│   ├── robot_geometry.hpp   ← Konstanta robot (radius, jarak, dsb)
│   ├── mecanum.hpp          ← Rumus matematika Mecanum (baca ini!)
│   └── omni.hpp             ← Rumus matematika Omni (baca ini!)
├── tests/
│   ├── test_mecanum.cpp     ← Test Mecanum (pure forward)
│   └── test_omni.cpp        ← Test Omni (pure forward)
├── launch/
│   └── demo.launch.py       ← Launch file demo
├── config/
│   └── robot_params.yaml    ← Parameter solver_type
├── answers/
│   ├── mecanum.cpp          ← Jawaban lengkap
│   └── omni.cpp             ← Jawaban lengkap
├── CMakeLists.txt           ← Konfigurasi build
├── package.xml              ← Dependensi package
└── AGENTS.MD                ← Panduan teknis untuk asisten/agent
```

---

## Tips
- Mulai dari **Mecanum** dulu, Omni mirip konsepnya.
- Gunakan konstanta dari `robot_geometry.hpp` (misal `wheel_radius`, `L`, `W`).
- `CG` = **Center of Gravity** (pusat massa robot) — titik acuan di tengah robot di mana kecepatan translasi dan rotasi diukur.
- Kalau hasil aneh (roda berputar terbalik), cek tanda `+`/`-` pada rumus.
- Jangan takut dengan test **FAIL** — itu tanda template bekerja dengan baik.

Selamat mengerjakan! 🚀
