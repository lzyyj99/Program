from tkinter import *
from tkinter import filedialog
import webbrowser
import os

filename = filedialog.askopenfilename()
print('文件选择完毕，路径为：', filename)

def Create_Window():  # 窗口
    window = Tk()
    window.title("单表破译工具")
    window.geometry('800x935')
    class decryptor1:

        def __init__(self):
            self.s = []  # 记录字符类型
            self.b = []  # 记录字符数目
            self.csum = 0  # 字符总数
            self.ssum = 0  # 字符类型总数
            self.cip = ""  # 密文
            self.es = []  # e在密文中的位置
            self.message = ""
            self.dictionary1 = {'e': 12.702, 't': 9.056, 'a': 8.167, 'o': 7.207, 'i': 6.996, 'n': 6.749, 's': 6.327,
                                'h': 6.094, 'r': 5.987,'d': 4.253, 'l': 4.025, 'c': 2.782, 'u': 2.758, 'm': 2.405, 'w': 2.361, 'f': 2.228,
                                'g': 2.015, 'y': 1.974, 'p': 1.929, 'b': 1.492, 'v': 0.978, 'k': 0.772,'j': 0.153, 'x': 0.150, 'q': 0.095, 'z': 0.074}
            self.dictionary2 =['e', 't', 'a', 'o', 'i', 'n', 's','h', 'r','d', 'l', 'c', 'u', 'm', 'w', 'f','g', 'y', 'p', 'b', 'v', 'k','j', 'x', 'q', 'z']
            self.dictionary3 ={}
            self.sortout = {}
            self.key = {}
            self.l = []

        def openfile(self, filename):
            f1 = open(filename, "r+", encoding='utf-8')
            self.cip = f1.read()
            self.message = self.cip

        def prinftext(self):
            t0 = Label(window, borderwidth = 3,relief="ridge")
            t0.place(x=400,y=20 , width=390 , height=230)
            t0 = Label(window, text="密文", font=('黑体', 15,'bold'))
            t0.place(x=420, y=10)
            t1 = Text(window, bg='white', font=('黑体', 12),padx=2, pady=2, borderwidth=2,relief="sunken")
            t1.insert(INSERT, f"{self.cip}")
            t1.place(x=410, y=40,width=370,height=200)

        def calcullate(self):
            for i in self.cip:
                if (i == ' ' or i == '\n'):
                    continue
                if not (i in self.s):  # 只记录字母
                    self.s.append(i)
                    self.b.append(0)
                    self.csum = self.csum + 1  # 记录字母总数
                    self.ssum = self.ssum + 1
                    for j in range(0, self.ssum):
                        if (self.s[j] == i):
                            self.b[j] = self.b[j] + 1
                elif i in self.s:
                    self.csum = self.csum + 1  # 记录字母总数
                    for j in range(0, self.ssum):
                        if (self.s[j] == i):
                            self.b[j] = self.b[j] + 1
            t2 = Label(window, borderwidth = 3,relief="ridge")
            t2.place(x=2,y=15 , width=380 , height=320)
            t3 = Label(window, text="密文信息概览", font=('黑体', 15, 'bold'))
            t3.place(x=32, y=5)
            t4 = Label(window, text=f"密文长度",font=('黑体', 12,'bold'))
            t4.place(x=5,y=40)
            t5 = Text(window,  bg='white',fg="black", font=('黑体', 11),padx=2, pady=2, borderwidth=2,relief="sunken")
            t5.insert(INSERT, f"{self.csum}")
            t5.place(x=85,y=40,width=50,height=22)
            t6 = Label(window, text=f"字符总数",font=('黑体', 12,'bold'))
            t6.place(x=5,y=70)
            t7 = Text(window, bg='white', font=('黑体', 11),padx=2, pady=2, borderwidth=2,relief="sunken")
            t7.insert(INSERT, f"{self.ssum}")
            t7.place(x=85, y=70,width=50,height=22)
            t8 = Label(window, text=f"包含字符", font=('黑体', 12,'bold'))
            t8.place(x=5,y=100)
            t9 = Text(window, bg='white', font=('黑体', 11), padx=2, pady=2, borderwidth=2, relief="sunken")
            t9.insert(INSERT, ' ,'.join(self.s))
            t9.place(x=85, y=100, width=280, height=100)
            ta = Label(window, text="各字符数", font=('黑体', 12,'bold'))
            ta.place(x=5,y=210)
            tb = Text(window, bg='white', font=('黑体', 11), padx=2, pady=2, borderwidth=2, relief="sunken")
            tb.insert(INSERT, " ,".join(str(i) for i in self.b) )
            tb.place(x=85, y=210, width=280, height=100)

        def sort(self):
            result = []
            n = self.ssum
            for i in range(n):
                for j in range(0, n - i-1):
                    if self.b[j] < self.b[j + 1]:
                        self.b[j], self.b[j + 1] = self.b[j + 1], self.b[j]
                        self.s[j], self.s[j + 1] = self.s[j + 1], self.s[j]
            for i in range(0, self.ssum):
                result.append((self.b[i] / self.csum))
            for i in range(0, self.ssum):
                self.sortout[self.s[i]]=round(result[i] * 100,4)
            tc = Label(window, borderwidth = 3,relief="ridge")
            tc.place(x=2,y=350 , width=380 , height=560)
            td = Label(window, text="统计分析", font=('黑体', 15, 'bold'))
            td.place(x=32, y=340)
            te = Label(window, text=f"各个字母频率", font=('黑体', 12,'bold'))
            te.place(x=5,y=370)
            tf = Text(window, bg='white', font=('黑体', 11), padx=2, pady=2, borderwidth=2, relief="sunken")
            tf.insert(INSERT, self.sortout)
            tf.place(x=10, y=400, width=365, height=140)

        def printdictionary(self):
            tg = Label(window, text=f"字典字母出现概率", font=('黑体', 12,'bold'))
            tg.place(x=5,y=550)
            th = Text(window, bg='white', font=('黑体', 11), padx=2, pady=2, borderwidth=2, relief="sunken")
            th.insert(INSERT, self.dictionary1)
            th.place(x=10, y=580, width=365, height=140)

        def advice(self):
            i = 0
            for a in self.sortout:
                self.dictionary3[a]=self.dictionary2[i]
                i = i+1
            ti = Label(window, text='建议对应关系', font=('黑体', 12,'bold'))
            ti.place(x=5,y=730)
            tj = Text(window, bg='white', font=('黑体', 11), padx=2, pady=2, borderwidth=2, relief="sunken")
            tj.insert(INSERT, self.dictionary3)
            tj.place(x=10, y=760, width=365, height=140)


        def findthe(self):
            e = self.s[0]
            select1 = []
            select2 = []
            select3 = []
            sum = 0
            esum = 0
            max2 = 0
            max3 = 0
            for i in self.cip:
                if i == e:
                    self.es.append(sum)
                    esum = esum + 1
                sum = sum + 1
            for j in range(esum):
                if self.es[j] >= 2:
                    select1.append(self.cip[self.es[j] - 2:self.es[j] + 1])
                    # print(self.cip[self.es[j]-2:self.es[j]+1])
                    if not (select1[j] in select2):
                        select2.append(select1[j])
                        select3.append(0)
            for k in range(len(select1)):
                for t in range(len(select2)):
                    if select2[t] == select1[k]:
                        select3[t] = select3[t] + 1
            for h in range(len(select2)):
                if select3[h] > max3:
                    max2 = h
                    max3 = select3[h]
            t0 = Label(window, borderwidth = 3,relief="ridge")
            t0.place(x=400,y=260 , width=390 , height=50)
            t0 = Label(window, text="上下文对应分析", font=('黑体', 15, 'bold'))
            t0.place(x=420, y=250)
            t9 = Text(window, bg='white', font=('黑体', 12),padx=2, pady=2, borderwidth=2,relief="sunken",)
            t9.insert(INSERT,f"若{e}为e，则{select2[max2]},是the",)
            t9.place(x=410,y=280,width=350,height=25)

        def inputkey(self):
            x1=410
            y1=380
            t=0
            t0 = Label(window, borderwidth = 3,relief="ridge")
            t0.place(x=400,y=350 , width=390 , height=150)
            t0 = Label(window, text="密钥输入", font=('黑体', 15, 'bold'))
            t0.place(x=420, y=340)
            for i in range(self.ssum):
                tx = Label(window, text=f"{self.s[i]}:",  font=('黑体', 12), wraplength=100)
                tx.place(x=x1+t*50,y=y1)
                xa = Entry(window, bg="white", font=('黑体', 12),bd=0, borderwidth=2, relief="sunken")
                xa.place(x=x1 + t * 50+25, y=y1,width=20, height=20)
                self.l.append(xa)
                t = t+1
                if(t > 6):
                    y1 = y1+25
                    t = t-7

        def conclude(self):
            for i in range(self.ssum):
                self.key[self.s[i]] = self.l[i].get()

        def decrypt(self):
            t11.place_forget()
            message1 = list(self.cip)
            for i in range(len(message1)):
                for j in self.s:
                    if message1[i] == j:
                        if(self.key[j]!=''):
                            message1[i] = self.key[j]
                            break
            #for i in range(len(self.key)):
                #if(self.key[self.s[i]]!=''):
                    #message1 = message1.replace(self.s[i], self.key[self.s[i]])
            self.message = ''.join(message1)
            t11.insert(INSERT,self.message)
            t11.place(x=410, y=550,width=370,height=200)
        def search(self):
            webbrowser.open("https://youdao.com/")
        def opendic(self):
            os.system("C:\\Users\\LiangZhaoYi\\Desktop\\密码学大作业\\英汉词典.txt")
        def destory1(self):
            window.destroy()
    def openfile():
        global filename
        filename = filedialog.askopenfilename()

    menubar = Menu(window)  # 菜单一
    filemenu = Menu(menubar, tearoff=0)  # 一级菜单
    menubar.add_cascade(label='File', menu=filemenu)  # 二级菜单
    filemenu.add_command(label='Open',command=openfile)
    editmenu = Menu(menubar, tearoff=0)  # 一级菜单
    menubar.add_cascade(label='Exit', menu=editmenu)  # 二级菜单
    editmenu.add_command(label='Exit', command=window.quit)
    window.config(menu=menubar)

    DEC = decryptor1()
    DEC.openfile(filename)
    DEC.prinftext()
    DEC.calcullate()
    DEC.sort()
    DEC.printdictionary()
    DEC.advice()
    DEC.findthe()
    DEC.inputkey()
    tq = Label(window, borderwidth=3, relief="ridge")
    tq.place(x=400, y=530, width=390, height=230)
    tw = Label(window, text="明文", font=('黑体', 15, 'bold'))
    tw.place(x=420, y=520)
    t11 = Text(window, bg='white', font=('黑体', 12,), padx=2, pady=2, borderwidth=2, relief="sunken")
    button1 = Button(window, text='解密', bg='white',font=('黑体', 12,), command=DEC.decrypt)
    button1.place(x=710, y=490 , width=40, height=20)
    button2 = Button(window, text='输入密钥', bg='white',font=('黑体', 12,), command=DEC.conclude)
    button2.place(x=620, y=490 , width=80, height=20)
    t0 = Label(window, borderwidth=3, relief="ridge")
    t0.place(x=400, y=770, width=390, height=80)
    t0 = Label(window, text="字典", font=('黑体', 15, 'bold'))
    t0.place(x=420, y=760)
    button3 = Button(window, text='有道词典', bg='white',font=('黑体', 18,), command=DEC.search)
    button3.place(x=430, y=790, width=120, height=50)
    button4 = Button(window, text='英汉词典', bg='white',font=('黑体', 18,), command=DEC.opendic)
    button4.place(x=580, y=790, width=120, height=50)
    button5 = Button(window, text='退出', bg='white',font=('黑体', 12,), command=DEC.destory1)
    button5.place(x=710, y=870, width=60, height=30)
    window.mainloop()

Create_Window()