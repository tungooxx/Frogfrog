#include "header/boss.h"
#include "header/global.h"
Boss::Boss() : shootTimer(20), ShootInterval(150)
{

	texture.loadFromFile("D:/test2/img/Frog.png");
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(CELL_SIZE * 0, CELL_SIZE * 3, CELL_SIZE, CELL_SIZE));
	float x = static_cast<short>(CELL_SIZE * floor(0.5f * MAP_WIDTH));
	float y = 8;
	sprite.setOrigin(CELL_SIZE/2.0f,CELL_SIZE/2.0f);
	sprite.setPosition(x,y);
}
void Boss::update(float fx, float fy)
{
	shootTimer++;
	if(shootTimer >= ShootInterval){
		shoot(fx,fy);
		shootTimer=0;
	}
	for(auto& bullet : bullets)
	{
		bullet.update(fx,fy);
	}


}
void Boss::draw(sf::RenderWindow& i_window, float fx,float fy)
{
	float x = static_cast<short>(CELL_SIZE * floor(0.5f * MAP_WIDTH));
	float y = 0;
	float angle = 180 - std::atan2(x-fx,y-fy) *180 / 3.14;
	sprite.setRotation(angle);
	for(auto& bullet : bullets){
	bullet.draw(i_window);
	}
	i_window.draw(sprite);
}

std::vector<Bullet>& Boss::getBullets()
{
	return bullets;
}

void Boss::shoot(float fx, float fy)
{
	float BulletX = sprite.getPosition().x + sprite.getGlobalBounds().width /2;
	float BulletY = sprite.getPosition().y + sprite.getGlobalBounds().height;

	float dirX = fx - BulletX;
	float dirY = fy - BulletY;
	bullets.emplace_back(BulletX,BulletY,dirX,dirY);
}
