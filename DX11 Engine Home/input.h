#pragma once
class input
{
public:
	input();
	~input();

	void Init();

	void KeyDown(unsigned int key);
	void KeyUp(unsigned int key);

	bool IsKeyDown(unsigned int key);

private:
	bool mKeys[256];
};

