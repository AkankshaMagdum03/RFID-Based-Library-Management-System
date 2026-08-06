-- ==========================================
-- RFID Library Management System Database
-- Author: Akanksha Magdum
-- Database: rfid_library
-- ==========================================

CREATE DATABASE IF NOT EXISTS rfid_library;
USE rfid_library;

DROP TABLE IF EXISTS book_logs;

CREATE TABLE book_logs (
    id INT AUTO_INCREMENT PRIMARY KEY,
    student_id VARCHAR(50) NOT NULL,
    book_id VARCHAR(100) NOT NULL,
    scan_time DATETIME NOT NULL,
    issue_date DATE NOT NULL,
    return_date DATE DEFAULT NULL,
    status ENUM('Issued','Returned') NOT NULL DEFAULT 'Issued'
);

-- ==========================================
-- Sample Record
-- ==========================================

INSERT INTO book_logs
(student_id, book_id, scan_time, issue_date, return_date, status)
VALUES
(
'21ST116331023',
'EMBEDDED SYSTEMS',
'2026-08-06 10:30:15',
'2026-08-06',
NULL,
'Issued'
);
