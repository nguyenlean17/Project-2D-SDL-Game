# Project Game 2D using SDL2 and C++
## 1.	Thông tin về game: 
• Tên game : Banish The Lord 

• Giải thích tên game : Để phù hợp với viết tắt "BTL" (Bài tập lớn).

•	Link Video Demo : https://www.youtube.com/watch?v=ID8A36aYPJg

•	Điều khiển : 

-	Ở Menu : di chuyển giữa các lựa chọn bằng W và S, chọn bằng E.

-	Ingame : Di chuyển né đạn bằng WASD, nhắm và bắn bằng chuột trái.


•	Link Github game : https://github.com/nguyenlean17/Project-2D-SDL-Game

•	Các nguồn tham khảo : Được truyền cảm hứng bởi các game Rogue-like như Souls Knight, Dark Souls, Binding of Isaac. 

•	Miêu tả về game : Game làm theo phong cách Bullet Hell, player điều khiển nhân vật bằng các phím WASD, bắn bằng chuột trái. Game kết thúc khi player bị trúng đạn, hoặc khi HP của Boss tụt đến 0. 
## 2.	Các tính năng cải tiến trong game
•	Hướng dẫn của kênh Let’s Make Games kết thúc khá sớm, và ý tưởng game của em và game gốc của kênh cũng khá khác nhau, nên phần lớn game của em là cải tiến từ hướng dẫn.

•	Các tính năng cải tiến : 

+ Main menu, lựa chọn level (Độ khó)

+ Boss, cách nhắm bắn, lựa chọn loại đạn của boss

+ Player nhắm bắn bằng chuột

+ Các loại đạn khác nhau

+ Sound effect và âm nhạc sử dụng SDL_Mixer.
## 3.	Cấu trúc của project game: Tổ chức lớp, Miêu tả luồng, …
•	Có sử dụng hệ thống Asset Manager để kiểm soát các texture, và hệ thống các Component để quản lí từng yếu tố của game. (Ví dụ các loại đạn thì có ProjectileComponent, điều khiển người chơi được làm trong KeyboardComponent)

•	Bài sử dụng nhiều class khác nhau để đại diện cho các tính năng riêng lẻ

•	Luồng của game : 

-	Khởi tạo (Initialize) cửa sổ, renderer SDL, SDL_ttf và SDL_image;

-	Đưa game vào GameState::MainMenu, render MainMenu;

-	Khi chọn Play, đưa game vào GameState::LevelSelect, render các lựa chọn level

-	Khi chọn level, đưa game vào GameState::Playing, và gán độ khó GameDifficulty

-	GameDifficulty thay đổi các biến về điểm HP của boss, tốc độ bắn, và hình ảnh map, boss.

-	Render lần lượt map, player, boss, và các projectiles.

-	Player được điều khiển bằng KeyboardProjectile.

-	Game liên tục kiểm tra : 1) Va chạm giữa player và đạn của boss và 2) Va chạm giữa boss và đạn của player,

-	Nếu 1) xảy ra : Chuyển sang GameState::GameOver, render menu GameOver.

-	Nếu 2) xảy ra : Trừ máu (HP) của Boss. Nếu HP của Boss giảm xuống 0: Chuyển sang GameState::GameWin, render menu GameWin.

-	Cả 2 menu trên đều có option Quit và Play Again, option Play Again đưa game về GameState::MainMenu, render Main Menu và đưa boss về trạng thái full HP.

-	Khi quit game (bằng option quit hoặc bằng nút ESC) : thực hiện hàm game::Clean(), giải phóng cửa sổ, renderer.
## 4.	Nguồn tham khảo và lấy dữ liệu: âm thanh, đồ họa, chatgpt, 
•	Tham khảo hướng dẫn của kênh Youtube Let’s Make Games : https://www.youtube.com/watch?v=QQzAHcojEKg&list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx

•	Trang thư viện của SDL : https://www.libsdl.org/

•	Tham khảo hướng dẫn của Lazy Foo : https://lazyfoo.net/tutorials/SDL/01_hello_SDL/index2.php

•	Có sự trợ giúp theo dạng hỏi các câu hỏi với GoogleAIStudio.

•	Asset projectiles và player được lấy từ các free asset pack trên Itch.io, texture map và boss lấy từ asset của game The Binding of Isaac được chia sẻ trên Internet. Các banner được generate bởi ChatGPT. Font chữ Silver tải trên Itch.io.

•	Music và sound effect được lấy từ các tựa game Elden Ring, Dark Souls, The Witcher 3


