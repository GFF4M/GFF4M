using UnityEngine;
using System.Collections;
using UnityEditor;
using System.IO;
using System.Text;

public class OutputLocationInfo : MonoBehaviour {
    /// <summary>
    /// 名前から不要な文字をトリム
    /// </summary>
    /// <param name="name"></param>
    /// <returns></returns>
    static string TrimModelName(string name)
    {
        string modelName = name.Split('(')[0];
        char[] trim = { ' ', '.' };
        while (true)
        {
            string trimString = modelName.TrimEnd(trim);
            if (trimString == modelName)
            {
                //トリムできた。
                break;
            }
            modelName = trimString;
        }
        return modelName;
    }
    [MenuItem("Window/配置情報 出力")]
    public static void ShowWindow()
    {
        GameObject location = GameObject.Find("Location");
        Transform[] locs = location.GetComponentsInChildren<Transform>();
        string outputTxt = "";
        //マップチップを出力。
        foreach (Transform tr in locs)
        {
            if (tr.parent != location.transform)
            {
                //親がLocationじゃない奴はスキップする。
                continue;
            }
            string modelName = TrimModelName(tr.name);
            outputTxt += string.Format("//{0}\n", modelName);
            outputTxt += "{\n";
            outputTxt += string.Format("\t\"{0}\",\n", modelName);
            outputTxt += string.Format("\tCVector3({0:f}f, {1:f}f, {2:f}f),             //平行移動\n", tr.localPosition.x, tr.localPosition.y, tr.localPosition.z);
            outputTxt += string.Format("\tCQuaternion({0:f}f, {1:f}f, {2:f}f, {3:f}f ), //回転\n", tr.localRotation.x, tr.localRotation.y, tr.localRotation.z, tr.localRotation.w);
            outputTxt += string.Format("\tCVector3({0:f}f, {1:f}f, {2:f}f),             //スケール\n", tr.localScale.x * -1.0f, tr.localScale.y, tr.localScale.z) ;
            outputTxt += "},\n";
        }
        string path = null;
        string dir = "";
        if (File.Exists("locInfoOutputPath.txt"))
        {
            StreamReader sr = new StreamReader("locInfoOutputPath.txt");
            dir = sr.ReadLine();
            if(dir == null)
            {
                dir = "";
            }
            sr.Close();
        }
        
        path = EditorUtility.SaveFilePanel("", dir,  "locationInfo.h", "h");
        //フォルダを記録する。
        StreamWriter sw = new StreamWriter("locInfoOutputPath.txt", false, Encoding.UTF8);
        sw.Write(System.IO.Path.GetDirectoryName(path));
        sw.Close();

        sw = new StreamWriter(path, false, Encoding.UTF8);
        sw.Write(outputTxt);
        sw.Close();
    }

    void OnGUI()
    {

    }
}
