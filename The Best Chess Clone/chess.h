#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string_view>
#include <unordered_map>
#include <map>

class Chess
{
	public:

		Chess(const Chess&) = delete;
		void operator=(const Chess&) = delete;
		Chess(int windowSize, std::string_view windowName);
		~Chess();

		void run();
		bool hadError();
		std::string_view getError();
		
	private:

		enum ErrorCode
		{
			None,
			SDL_init,
			SDL_IMG_init,
			Window_init,
			Render_init,
			IMG_load,
			Texture_load,
		};

		struct Piece
		{
			enum Color 
			{
				White,
				Black,
			};

			enum Type
			{
				Pawn,
				Knight,
				Bishop,
				Rook,
				Queen,
				King,
			};

			Color color;
			Type type;

			int getID() const;
		};

		struct PieceComparator
		{
			bool operator()(const Chess::Piece& left, const Chess::Piece& right) const;
		};

		static std::unordered_map<ErrorCode, std::string_view> m_errorMap;

		const int m_squaresPerLine{ 8 };
		const int m_windowSize{};
		const int m_squareSize{};

		SDL_Window* m_window{ nullptr };
		SDL_Renderer* m_renderer{ nullptr };
		SDL_Texture* m_boardTexture{ nullptr };
		std::map<Piece, SDL_Texture*, PieceComparator> m_pieceTextureMap;
		
		ErrorCode m_errorCode{ ErrorCode::None };

		bool init(std::string_view windowName);
		bool loadResources();
		bool loadTexture(SDL_Texture*& texturePtr, std::string_view path);
};