// DOM Elements
const chapterSelect = document.getElementById('chapter-select');
const modeSequential = document.getElementById('mode-sequential');
const modeRandom = document.getElementById('mode-random');
const statsTotalDisplay = document.getElementById('stats-total');
const statsWrongDisplay = document.getElementById('stats-wrong');
const btnPracticeWrong = document.getElementById('btn-practice-wrong');
const btnClearStats = document.getElementById('btn-clear-stats');

const welcomeScreen = document.getElementById('welcome-screen');
const questionScreen = document.getElementById('question-screen');
const resultScreen = document.getElementById('result-screen');

const btnStartQuiz = document.getElementById('btn-start-quiz');
const btnRestart = document.getElementById('btn-restart');
const btnNext = document.getElementById('btn-next');

const currentChapterText = document.getElementById('current-chapter-name');
const quizProgressText = document.getElementById('quiz-progress-text');
const progressFill = document.getElementById('progress-fill');

const qIdxDisplay = document.getElementById('q-idx');
const qTextDisplay = document.getElementById('q-text');
const optionsContainer = document.getElementById('options-container');
const feedbackArea = document.getElementById('feedback');
const feedbackText = document.getElementById('feedback-text');

const resultScore = document.getElementById('result-score');
const resultTotal = document.getElementById('result-total');
const resultAccuracy = document.getElementById('result-accuracy');

// App State
let currentQuestions = [];
let currentIndex = 0;
let score = 0;
let isAnswered = false;
let practiceMode = 'sequential'; // 'sequential' or 'random'
let wrongAnswersBank = JSON.parse(localStorage.getItem('ooad_wrong_answers')) || [];
let totalAnsweredCount = parseInt(localStorage.getItem('ooad_total_answered')) || 0;

// Initialize
function init() {
    // Populate Chapter Select
    questionBank.forEach((chap, idx) => {
        const option = document.createElement('option');
        option.value = idx;
        option.textContent = chap.chapter;
        chapterSelect.appendChild(option);
    });

    updateStatsDisplay();

    // Event Listeners
    modeSequential.addEventListener('click', () => setMode('sequential'));
    modeRandom.addEventListener('click', () => setMode('random'));
    btnStartQuiz.addEventListener('click', startQuiz);
    btnRestart.addEventListener('click', () => showScreen(welcomeScreen));
    btnNext.addEventListener('click', showNextQuestion);
    btnPracticeWrong.addEventListener('click', startWrongPractice);
    btnClearStats.addEventListener('click', clearStats);
}

function updateStatsDisplay() {
    statsTotalDisplay.textContent = totalAnsweredCount;
    statsWrongDisplay.textContent = wrongAnswersBank.length;
}

function setMode(mode) {
    practiceMode = mode;
    modeSequential.classList.toggle('active', mode === 'sequential');
    modeRandom.classList.toggle('active', mode === 'random');
}

function showScreen(screen) {
    [welcomeScreen, questionScreen, resultScreen].forEach(s => s.classList.add('hidden'));
    screen.classList.remove('hidden');
}

function startQuiz() {
    const selectedVal = chapterSelect.value;
    let pool = [];

    if (selectedVal === 'all') {
        questionBank.forEach(chap => {
            chap.questions.forEach(q => pool.push({ ...q, chapter: chap.chapter }));
        });
        currentChapterText.textContent = "全部章节";
    } else {
        const chap = questionBank[selectedVal];
        pool = chap.questions.map(q => ({ ...q, chapter: chap.chapter }));
        currentChapterText.textContent = chap.chapter;
    }

    if (practiceMode === 'random') {
        pool = shuffleArray(pool);
    }

    currentQuestions = pool;
    currentIndex = 0;
    score = 0;
    
    showScreen(questionScreen);
    showQuestion();
}

function startWrongPractice() {
    if (wrongAnswersBank.length === 0) {
        alert("目前还没有错题记录哦！");
        return;
    }

    currentQuestions = shuffleArray([...wrongAnswersBank]);
    currentChapterText.textContent = "错题复习";
    currentIndex = 0;
    score = 0;

    showScreen(questionScreen);
    showQuestion();
}

function showQuestion() {
    isAnswered = false;
    const q = currentQuestions[currentIndex];
    
    qIdxDisplay.textContent = `Q${currentIndex + 1}.`;
    qTextDisplay.textContent = q.question;
    
    // Progress
    const progress = ((currentIndex) / currentQuestions.length) * 100;
    progressFill.style.width = `${progress}%`;
    quizProgressText.textContent = `${currentIndex + 1} / ${currentQuestions.length}`;

    // Options
    optionsContainer.innerHTML = '';
    feedbackArea.classList.add('hidden');
    btnNext.classList.add('hidden');

    Object.entries(q.options).forEach(([letter, text]) => {
        const item = document.createElement('div');
        item.className = 'option-item';
        item.innerHTML = `<span class="opt-letter">${letter}.</span> <span class="opt-text">${text}</span>`;
        item.addEventListener('click', () => handleAnswer(letter, item));
        optionsContainer.appendChild(item);
    });
}

function handleAnswer(selectedLetter, element) {
    if (isAnswered) return;
    isAnswered = true;

    const q = currentQuestions[currentIndex];
    const isCorrect = selectedLetter === q.answer;

    // Track statistics for globally unique questions
    // Since questions might repeat across sessions, we just increment total count
    totalAnsweredCount++;
    localStorage.setItem('ooad_total_answered', totalAnsweredCount);

    if (isCorrect) {
        score++;
        element.classList.add('correct');
        feedbackArea.className = 'feedback correct';
        feedbackText.textContent = "正确！太棒了。";
        
        // Remove from wrong answers if it was there
        removeFromWrongBank(q);
    } else {
        element.classList.add('incorrect');
        // Highlight correct one
        Array.from(optionsContainer.children).forEach(child => {
            if (child.querySelector('.opt-letter').textContent.startsWith(q.answer)) {
                child.classList.add('correct');
            }
        });
        feedbackArea.className = 'feedback incorrect';
        feedbackText.textContent = `回答错误。正确答案是 ${q.answer}`;
        
        // Add to wrong answers bank
        addToWrongBank(q);
    }

    feedbackArea.classList.remove('hidden');
    btnNext.classList.remove('hidden');
    
    if (currentIndex === currentQuestions.length - 1) {
        btnNext.textContent = "查看结果";
    } else {
        btnNext.textContent = "下一题";
    }

    updateStatsDisplay();
}

function showNextQuestion() {
    currentIndex++;
    if (currentIndex < currentQuestions.length) {
        showQuestion();
    } else {
        finishQuiz();
    }
}

function finishQuiz() {
    showScreen(resultScreen);
    progressFill.style.width = '100%';
    
    resultScore.textContent = score;
    resultTotal.textContent = currentQuestions.length;
    const accuracy = Math.round((score / currentQuestions.length) * 100);
    resultAccuracy.textContent = `${accuracy}%`;
}

// Help Functions
function shuffleArray(array) {
    for (let i = array.length - 1; i > 0; i--) {
        const j = Math.floor(Math.random() * (i + 1));
        [array[i], array[j]] = [array[j], array[i]];
    }
    return array;
}

function addToWrongBank(question) {
    const exists = wrongAnswersBank.find(q => q.question === question.question);
    if (!exists) {
        wrongAnswersBank.push(question);
        localStorage.setItem('ooad_wrong_answers', JSON.stringify(wrongAnswersBank));
    }
}

function removeFromWrongBank(question) {
    const freshBank = wrongAnswersBank.filter(q => q.question !== question.question);
    if (freshBank.length !== wrongAnswersBank.length) {
        wrongAnswersBank = freshBank;
        localStorage.setItem('ooad_wrong_answers', JSON.stringify(wrongAnswersBank));
    }
}

function clearStats() {
    if (confirm("确定要清空所有练习记录和错题吗？")) {
        localStorage.removeItem('ooad_wrong_answers');
        localStorage.removeItem('ooad_total_answered');
        wrongAnswersBank = [];
        totalAnsweredCount = 0;
        updateStatsDisplay();
    }
}

// Run!
init();
