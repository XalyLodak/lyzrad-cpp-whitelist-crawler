CREATE DATABASE IF NOT EXISTS myapp;
USE myapp;

CREATE TABLE users (
    id          INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    email       VARCHAR(255) NOT NULL UNIQUE,
    username    VARCHAR(64)  NOT NULL UNIQUE,
    pseudonym   VARCHAR(64)  NOT NULL,
    passwordHash VARCHAR(255) NOT NULL,
    whitelisted TINYINT(1)   NOT NULL DEFAULT 0,
    banned TINYINT(1)   NOT NULL DEFAULT 0
);

INSERT INTO users (email, username, pseudonym, passwordHash, whitelisted) VALUES
('player1@example.com',  'player1',      'Player_1', 'hash_placeholder', 1),
('player2@example.com',  'player2',   'Player2', 'hash_placeholder', 0);