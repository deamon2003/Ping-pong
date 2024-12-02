#include "raylib.h"

int main() {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Ping Pong Game");
    SetTargetFPS(60);

    // Ball properties
    Vector2 ballPosition = { screenWidth / 2.0f, screenHeight / 2.0f };
    Vector2 ballSpeed = { 4.0f, 4.0f };
    const float ballRadius = 10.0f;

    // Paddle properties
    const int paddleWidth = 10;
    const int paddleHeight = 100;
    const float paddleSpeed = 6.0f;

    Rectangle player1Paddle = { 20, (float)(screenHeight / 2 - paddleHeight / 2), (float)paddleWidth, (float)paddleHeight };
    Rectangle player2Paddle = { (float)(screenWidth - 30), (float)(screenHeight / 2 - paddleHeight / 2), (float)paddleWidth, (float)paddleHeight };

    int player1Score = 0;
    int player2Score = 0;

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        // Player 1 controls (W/S)
        if (IsKeyDown(KEY_W) && player1Paddle.y > 0) player1Paddle.y -= paddleSpeed;
        if (IsKeyDown(KEY_S) && player1Paddle.y < screenHeight - paddleHeight) player1Paddle.y += paddleSpeed;

        // Player 2 controls (Up/Down arrows)
        if (IsKeyDown(KEY_UP) && player2Paddle.y > 0) player2Paddle.y -= paddleSpeed;
        if (IsKeyDown(KEY_DOWN) && player2Paddle.y < screenHeight - paddleHeight) player2Paddle.y += paddleSpeed;

        // Move ball
        ballPosition.x += ballSpeed.x;
        ballPosition.y += ballSpeed.y;

        // Ball collision with top and bottom walls
        if (ballPosition.y <= ballRadius || ballPosition.y >= screenHeight - ballRadius) {
            ballSpeed.y *= -1; // Reverse vertical direction
        }

        // Ball collision with paddles
        if (CheckCollisionCircleRec(ballPosition, ballRadius, player1Paddle)) {
            ballSpeed.x *= -1.1f; // Reverse horizontal direction and increase speed
            ballPosition.x = player1Paddle.x + paddleWidth + ballRadius; // Prevent sticking
        }
        if (CheckCollisionCircleRec(ballPosition, ballRadius, player2Paddle)) {
            ballSpeed.x *= -1.1f;
            ballPosition.x = player2Paddle.x - ballRadius; // Prevent sticking
        }

        // Check for scoring
        if (ballPosition.x < 0) {
            player2Score++;
            ballPosition = { screenWidth / 2.0f, screenHeight / 2.0f };
            ballSpeed = { 4.0f, 4.0f };
        }
        if (ballPosition.x > screenWidth) {
            player1Score++;
            ballPosition = { screenWidth / 2.0f, screenHeight / 2.0f };
            ballSpeed = { -4.0f, -4.0f };
        }

        // Draw
        BeginDrawing();
        ClearBackground(BLACK);

        // Draw ball
        DrawCircleV(ballPosition, ballRadius, WHITE);

        // Draw paddles
        DrawRectangleRec(player1Paddle, WHITE);
        DrawRectangleRec(player2Paddle, WHITE);

        // Draw score
        DrawText(TextFormat("%d", player1Score), screenWidth / 4, 20, 40, WHITE);
        DrawText(TextFormat("%d", player2Score), 3 * screenWidth / 4, 20, 40, WHITE);

        DrawText("Ping Pong Game!", screenWidth / 2 - 100, screenHeight - 40, 20, GRAY);

        EndDrawing();
    }

    // De-Initialization
    CloseWindow();

    return 0;
}

